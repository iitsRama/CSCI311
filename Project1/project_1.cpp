#include <iostream>
using namespace std;
#include <vector>
#include <time.h>
#include <math.h>
#include <chrono>
#include <fstream>

bool isSorted(const vector<int> &v)
{
    if (v.size() < 2) { return true; }

    for (int i = 1; i < v.size(); i++)
    {
        if (v[i-1] > v[i])
        {
            return false;
        }
    }
    return true;
}

void bubbleSort(vector<int> &v)
{
    if (v.size() < 2) { return; }

    vector<int> vCopy = v;
    bool sorted = false;

    while(!sorted)
    {
        sorted = true;

        for(int i = 1; i < v.size(); i++)
        {
            if(v[i-1] > v[i])
            {
                int temp = v[i-1];
                v[i-1] = v[i];
                v[i] = temp;
                sorted = false;
            }
        }
    }
}

void insertionSort(vector<int> &v)
{
    if (v.size() < 2) { return; }

    for(int i = 1; i < v.size(); i++)
    {
        for(int j = i; j > 0 && v[j] < v[j-1]; j--)
        {
            int temp = v[j-1];
            v[j-1] = v[j];
            v[j] = temp;
        }
    }
}

void selectionSort(vector<int> &v)
{
    if (v.size() < 2) { return; }

    for(int i = 0; i < v.size() - 1; i++)
    {
        int uMin = i;
        for(int j = i + 1; j < v.size(); j++)
        {
            if(v[j] < v[uMin])
            {
                uMin = j;
            }
        }
        int temp = v[i];
        v[i] = v[uMin];
        v[uMin] = temp;
    }
}

void quickSort(vector<int> &v)
{
    if (v.size() < 2) { return; }

    int pivot = v[0];
    vector<int> A;
    vector<int> B;

    for(int i = 1; i < v.size(); i++)
    {
        if(v[i] <= pivot)
        {
            A.push_back(v[i]);
        }
        else
        {
            B.push_back(v[i]);
        }
    }

    quickSort(A);
    quickSort(B);

    v = A;
    v.push_back(pivot);
    for(int j = 0; j < B.size(); j++)
    {
        v.push_back(B[j]);
    }
}

void bestQuickSort(vector<int> &v)
{
    if (v.size() < 2) { return; }

    int pivot = v[v.size() / 2];
    vector<int> A;
    vector<int> B;

    for(int i = 0; i < v.size(); i++)
    {
        if(v[i] == pivot) { continue; };
        if(v[i] <= pivot)
        {
            A.push_back(v[i]);
        }
        else
        {
            B.push_back(v[i]);
        }
    }

    bestQuickSort(A);
    bestQuickSort(B);

    v = A;
    v.push_back(pivot);
    for(int j = 0; j < B.size(); j++)
    {
        v.push_back(B[j]);
    }
}

// void printVector(const vector<int> &v)
// {
//     std:: cout << v.size() << std::endl;
//     std::cout << "{";

//     if(v.size() == 0)
//     {
//         std::cout << "}" << std::endl;
//         return;
//     }
//     for(int i = 0; i < v.size() - 1; i++)
//     {
//         std::cout << v[i] << ", ";
//     }
//     std::cout << v[v.size() - 1] << "}" << std::endl;
// }

/******************************************************************
* Calculate the sample standard deviation of a vector of doubles *
* v - const vector<double> - a vector of doubles *
* return - double - the sample standard deviation of v *
******************************************************************/
double sampleSD(const vector<double> &v)
{
    double mean = 0;
    for (int i = 0; i < v.size(); i++)
    {
        mean += v[i];
    }
    mean = mean / v.size();
    double sd = 0;
    for (int i = 0; i < v.size(); i++)
    {
        sd += (v[i]-mean)*(v[i]-mean);
    }
    sd = sd / (v.size()-1);
    return sqrt(sd);
}

double timeSort(vector<int> &v, void (*sortFunc)(std::vector<int>&))
{
    chrono::high_resolution_clock::time_point start;
    chrono::high_resolution_clock::time_point end;

    start = chrono::high_resolution_clock::now();
    sortFunc(v);
    end = chrono::high_resolution_clock::now();

    double elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();

    return elapsed;
}

vector<double> calculateTime(const vector<double> &v)
{
    // <Min, Mean, StdDev, Max

    vector<double> timeOutliers;

    double minimum = v[0];
    double maximum = v[0];
    double sum = v[0];

    for(int i = 1; i < v.size(); i++)
    {
        sum += v[i];
        if(v[i] < minimum)
        {
            minimum = v[i];
        }
        if(v[i] > maximum)
        {
            maximum = v[i];
        }
    }

    double mean = sum / v.size();

    double stdDev = sampleSD(v);
    
    timeOutliers.push_back(minimum);
    timeOutliers.push_back(mean);
    timeOutliers.push_back(stdDev);
    timeOutliers.push_back(maximum);

    return timeOutliers;
}

// passing list by value makes a copy, lets me modify list all I want
void printVector(std::string sortName, vector<vector<int>> list, std::ofstream &file, void (*sortFunc)(std::vector<int>&))
{
    vector<double> timeValues;
    vector<double> timeOutliers;
    bool sorted = true;

    // std::cout << "*************************" << std::endl;
    // std::cout << sortName << " sort on " << list.size() << " vectors of length " << list[0].size() << std::endl;
    for(int i = 0; i < list.size(); i++)
    {

        //printVector(list[i]);
        double timeValue = timeSort(list[i], sortFunc);
        timeValues.push_back(timeValue);
        file << sortName << "," << list[i].size() << "," << timeValue << std::endl;
        sorted = sorted && isSorted(list[i]);
    }

    // (sorted) ? std::cout << "Sorting successful\n" : std::cout <<  "Sorting failed\n";
    
    timeOutliers = calculateTime(timeValues);

    // std::cout << "Minimum: " << timeOutliers[0] << "; Mean: " << timeOutliers[1] << "; Standard Deviation: " << timeOutliers[2] << "; Maximum: " << timeOutliers[3] << std::endl;
    // std::cout << std::endl;
    // std::cout << "*************************\n" << std::endl;
}

void printVector(std::string sortName, vector<vector<int>> list, void (*sortFunc)(std::vector<int>&))
{
    vector<double> timeValues;
    vector<double> timeOutliers;
    bool sorted = true;

    std::cout << "*************************" << std::endl;
    std::cout << sortName << " sort on " << list.size() << " vectors of length " << list[0].size() << std::endl;
    for(int i = 0; i < list.size(); i++)
    {

        //printVector(list[i]);
        double timeValue = timeSort(list[i], sortFunc);
        timeValues.push_back(timeValue);
        sorted = sorted && isSorted(list[i]);
    }

    (sorted) ? std::cout << "Sorting successful\n" : std::cout <<  "Sorting failed\n";
    
    timeOutliers = calculateTime(timeValues);

    std::cout << "Minimum: " << timeOutliers[0] << "; Mean: " << timeOutliers[1] << "; Standard Deviation: " << timeOutliers[2] << "; Maximum: " << timeOutliers[3] << std::endl;
    std::cout << std::endl;
    std::cout << "*************************\n" << std::endl;
}

/******************************************************************************
* Generate a vector of random integers in a given range. The ends *
* of this range are inclusive. *
* size - int - the number of integers in the resulting vector *
* low, high - int - the range from which to draw random integers (inclusive) *
* return - vector<int> - a vector of random integers *
******************************************************************************/
vector<vector<int>> randomVector(int size, int low, int high, int amount)
{
    vector<vector<int>> list;
    vector<int> v(size);

    for (int i = 0; i < amount; i++)
    {
        for(int j = 0; j < size; j++)
        {
            v[j] = rand() % (high - low + 1) + low;
        }
        list.push_back(v);
    }

    return list;
}

vector<vector<int>> sortedVector(int size, int low, int high, int amount)
{
    vector<vector<int>> list;
    vector<int> v(size);

    for(int i = 0; i < amount; i++)
    {
         int start = low + (size - 1) + rand() % (high - low - (size - 1) + 1);
        for(int j = 0; j < size; j++)
        {
            v[j] = start + j;
        }
        list.push_back(v);
    }

    return list;
}

vector<vector<int>> reverseSortedVector(int size, int low, int high, int amount)
{
    vector<vector<int>> list;
    vector<int> v(size);

    for(int i = 0; i < amount; i++)
    {
        int start = low + rand() % (high - low - (size - 1) + 1);
        for(int j = 0; j < size; j++)
        {
            v[j] = start - j;
        }
        list.push_back(v);
    }

    return list;
}

vector<vector<int>> worstSelectionVector(int size, int low, int high, int amount)
{
    vector<vector<int>> list;
    list.reserve(amount);

    for(int t = 0; t < amount; t++)
    {
        int hi = 100000 + rand() % (250000 - 100000 + 1);

        int half = size / 2;

        int difference = hi / half;
        if (difference < 2) difference = 2;
        if (difference % 2 != 0) difference++; 

        vector<int> v(size);

        int even = low;
        int odd  = hi - 1;

        // first half: ascending evens
        for(int i = 0; i < size/2; i++)
        {
            v[i] = even;
            even += difference;
        }

        // second half: descending odds
        for(int i = size/2; i < size; i++)
        {
            v[i] = odd;
            odd -= difference;
        }

        list.push_back(v);
    }

    return list;
}

void runTests(vector<vector<int>> &v, int low, int high, int amount, std::ofstream &file,
                void (*sortFunc)(std::vector<int>&), std::string sortName, char caseName)
{
    std::vector<int> sizes = {100, 200, 400, 800, 1600, 3200, 6400, 12800};

    for(int i = 0; i < sizes.size(); i++)
    {
        int difference;
        if(high < sizes[sizes.size() - 1])
        {
            difference = high / (high / 2);
        }
        else
        {
            difference = high / (sizes[i] / 2);
        }

        switch(caseName)
        {
            case 'b':
                v = sortedVector(sizes[i], low, high, amount);
                break;
            case 'a':
                v = randomVector(sizes[i], low, high, amount);
                break;
            case 'w':
                v = reverseSortedVector(sizes[i], low, high, amount);
                break;
            case 's':
                v = worstSelectionVector(sizes[i], low, high, amount);
                break;
            default:
                return;
        }
        printVector(sortName, v, file, sortFunc);
    }
}

void runTests(vector<vector<int>> &v, int startValue, int endValue, int amount,
                void (*sortFunc)(std::vector<int>&), std::string sortName, char caseName)
{
    int size = 100;

    if(caseName == 's')
    {
        v = worstSelectionVector(size, startValue, endValue, amount);
    }
    else
    {
        v = randomVector(size, startValue, endValue, amount);
    }

    printVector(sortName, v, sortFunc);
}

int main()
{
    std::ofstream worstFile("data/worst.csv");
    std::ofstream averageFile("data/average.csv");
    std::ofstream bestFile("data/best.csv");

    srand(time(NULL));

    vector<vector<int>> v;

    int low = 0;
    int high = 100000 + rand() % (250000 - 100000 + 1);
    int amount = 50;

    //runTests(v, low, high, 10, selectionSort, "Selection", 's');

    runTests(v, low, high, 10, bubbleSort, "Bubble", 'a');
    runTests(v, low, high, 10, insertionSort, "Insertion", 'a');
    runTests(v, low, high, 10, selectionSort, "Selection", 'a');
    runTests(v, low, high, 10, quickSort, "Quick", 'a');

    runTests(v, low, high, amount, bestFile, bubbleSort, "Bubble", 'b');
    runTests(v, low, high, amount, averageFile, bubbleSort, "Bubble", 'a');
    runTests(v, low, high, amount, worstFile, bubbleSort, "Bubble", 'w');

    runTests(v, low, high, amount, bestFile, insertionSort, "Insertion", 'b');
    runTests(v, low, high, amount, averageFile, insertionSort, "Insertion", 'a');
    runTests(v, low, high, amount, worstFile, insertionSort, "Insertion", 'w');

    runTests(v, low, high, amount, bestFile, selectionSort, "Selection", 'b');
    runTests(v, low, high, amount, averageFile, selectionSort, "Selection", 'a');
    runTests(v, low, high, amount, worstFile, selectionSort, "Selection", 's');

    runTests(v, low, high, amount, bestFile, bestQuickSort, "Quick", 'b');
    runTests(v, low, high, amount, averageFile, quickSort, "Quick", 'a');
    runTests(v, low, high, amount, worstFile, quickSort, "Quick", 'w');

    worstFile.close();
    averageFile.close();
    bestFile.close();

    return 0;
};