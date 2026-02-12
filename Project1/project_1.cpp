#include <iostream>
using namespace std;
#include <vector>
#include <time.h>
#include <math.h>
#include <chrono>
#include <fstream>

bool isSorted(const vector<int> &v)
{
    for (int i = 1; i < v.size(); i++)
    {
        if (v[i-1] > v[i])
        {
            return false;
        }
    }
    return true;
}

vector<int> bubbleSort(vector<int> &v)
{
    if (v.size() < 2) { return v; }

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

    return v;
}

vector<int> insertionSort(vector<int> &v)
{
    if (v.size() < 2) { return v; }

    for(int i = 1; i < v.size(); i++)
    {
        for(int j = i; j > 0 && v[j] < v[j-1]; j--)
        {
            int temp = v[j-1];
            v[j-1] = v[j];
            v[j] = temp;
        }
    }
 
    return v;
}

vector<int> selectionSort(vector<int> &v)
{
    if (v.size() < 2) { return v; }

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

    return v;
}

vector<int> quickSort(vector<int> &v)
{
    if (v.size() < 2) { return v; }

    int pivot = v[0];
    vector<int> A = {};
    vector<int> B = {};

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

    A = quickSort(A);
    B = quickSort(B);

    v = A;
    v.push_back(pivot);
    for(int j = 0; j < B.size(); j++)
    {
        v.push_back(B[j]);
    }

    return v;
}

vector<int> bestQuickSort(vector<int> &v)
{
    if (v.size() < 2) { return v; }

    int pivot = v[v.size() / 2];
    vector<int> A = {};
    vector<int> B = {};

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

    A = quickSort(A);
    B = quickSort(B);

    v = A;
    v.push_back(pivot);
    for(int j = 0; j < B.size(); j++)
    {
        v.push_back(B[j]);
    }

    return v;
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

double timeSort(vector<int> &v, std::vector<int> (*sortFunc)(std::vector<int>&))
{
    chrono::high_resolution_clock::time_point start;
    chrono::high_resolution_clock::time_point end;

    start = chrono::high_resolution_clock::now();
    v = sortFunc(v);
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
void printVector(std::string sortName, vector<vector<int>> list, std::ofstream &file, std::vector<int> (*sortFunc)(std::vector<int>&))
{
    vector<double> timeValues;
    vector<double> timeOutliers;
    bool sorted = true;

    std::cout << "*************************" << std::endl;
    std::cout << sortName << " sort on " << list.size() << " vectors of length " << list[0].size() << std::endl;
    for(int i = 0; i < list.size(); i++)
    {

        // printVector(list[i]);
        double timeValue = timeSort(list[i], sortFunc);
        timeValues.push_back(timeValue);
        file << sortName << ", " << list[i].size() << ", " << timeValue << std::endl;
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
        int random = rand() % (high - low + 1) + low;
        for(int j = 0; j < size; j++)
        {
            v[j] = random;
            random++;
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
        int random = rand() % (high - low + 1) + low;
        for(int j = 0; j < size; j++)
        {
            v[j] = random;
            random--;
        }
        list.push_back(v);
    }

    return list;
}

void runTests(vector<vector<int>> &v, int startSize, int endSize, int startValue, int endValue, int amount, std::ofstream &file,
     std::vector<int> (*sortFunc)(std::vector<int>&), std::string sortName, char caseName)
{
    for(int i = startSize; i <= endSize; i *= 10)
    {
        switch(caseName)
        {
            case 'b':
                v = sortedVector(i, startValue, endValue, amount);
                break;
            case 'a':
                v = randomVector(i, startValue, endValue, amount);
                break;
            case 'w':
                v = reverseSortedVector(i, startValue, endValue, amount);
                break;
            default:
                return;
        }
        printVector(sortName, v, file, sortFunc);
    }
}

int main()
{
    std::ofstream worstFile("worst.csv");
    std::ofstream averageFile("average.csv");
    std::ofstream bestFile("best.csv");

    srand(time(NULL));

    vector<vector<int>> average;
    vector<vector<int>> best;
    vector<vector<int>> worst;
    vector<vector<int>> bestQuick;
    vector<vector<int>> worstSelection;

    int startSize = 10;
    int endSize = 10000;
    int startValue = -1000000;
    int endValue = 1000000;
    int amount = 50;

    //std::vector<int> (*sortFunc)(std::vector<int>&)

    runTests(best, startSize, endSize, startValue, endValue, amount, bestFile, bubbleSort, "Bubble", 'b');
    runTests(average, startSize, endSize, startValue, endValue, amount, bestFile, bubbleSort, "Bubble", 'a');
    runTests(worst, startSize, endSize, startValue, endValue, amount, bestFile, bubbleSort, "Bubble", 'w');

    runTests(best, startSize, endSize, startValue, endValue, amount, bestFile, insertionSort, "Insertion", 'b');
    runTests(average, startSize, endSize, startValue, endValue, amount, bestFile, insertionSort, "Insertion", 'a');
    runTests(worst, startSize, endSize, startValue, endValue, amount, bestFile, insertionSort, "Insertion", 'w');

    runTests(best, startSize, endSize, startValue, endValue, amount, bestFile, selectionSort, "Selection", 'b');
    runTests(average, startSize, endSize, startValue, endValue, amount, bestFile, selectionSort, "Selection", 'a');
    runTests(worst, startSize, endSize, startValue, endValue, amount, bestFile, selectionSort, "Selection", 'w');

    runTests(best, startSize, endSize, startValue, endValue, amount, bestFile, quickSort, "Quick", 'b');
    runTests(average, startSize, endSize, startValue, endValue, amount, bestFile, quickSort, "Quick", 'a');
    runTests(worst, startSize, endSize, startValue, endValue, amount, bestFile, quickSort, "Quick", 'w');

    worstFile.close();
    averageFile.close();
    bestFile.close();

    return 0;
};


/*
D: For the best case for quicksort, we need to have 50 x 5 = 250 vectors,
and according to the quicksort algorithm (where we select the first
element to be the pivot element), we need to make sure the first element
of the vector is the median value of the whole vector, and then when you
go to the next round, you also need to make sure the first element of the
subvector is also the median value of that subvector, etc.

E: For the worst case for selection sort, e.g., you need to generate a
vector like this, {2,4,6,8,9,7,5,3,1}, to make sure every time the
selection works you need to do both the scanning and data swapping.
(ascending even numbers followed by descending odd numbers)

In summary,
A: 250 vectors that contain random numbers.
B: 250 vectors that are already sorted.
C: 250 vectors that are already reversely sorted.
D: 250 special vectors, as described above.
E: 250 special vectors, as described above.
*/