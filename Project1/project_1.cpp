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
        if (v[i-1] > v[i]) return false;
    }
    return true;
}

vector<int> bubbleSort(vector<int> &v)
{
    if (v.size() < 2) return v;

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
    if (v.size() < 2) return v;

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

vector<int> selecionSort(vector<int> &v)
{
    if (v.size() < 2) return v;

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
    if (v.size() < 2) return v;

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

void printVector(const vector<int> &v)
{
    std:: cout << v.size() << std::endl;
    std::cout << "{";
    if(v.size() == 0)
    {
        std::cout << "}" << std::endl;
        return;
    }
    for(int i = 0; i < v.size() - 1; i++)
    {
        std::cout << v[i] << ", ";
    }
    std::cout << v[v.size() - 1] << "}" << std::endl;
}

/******************************************************************************
* Generate a vector of random integers in a given range. The ends *
* of this range are inclusive. *
* size - int - the number of integers in the resulting vector *
* low, high - int - the range from which to draw random integers (inclusive) *
* return - vector<int> - a vector of random integers *
******************************************************************************/
vector<int> randomVector(int size, int low, int high)
{
    vector<int> v(size, 0);
    for (int i = 0; i < size; i++)
    {
        v[i] = rand() % (high - low +1) + low;
    }
    return v;
}

/******************************************************************
* Calculate the sample standard deviation of a vector of doubles *
* v - const vector<double> - a vector of doubles *
* return - double - the sample standard deviation of v *
******************************************************************/
double sampleSD(const vector<double> v)
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

double timeSort(const vector<int> &v, std::vector<int> (*sortFunc)(std::vector<int>&))
{
    chrono::high_resolution_clock::time_point start;
    chrono::high_resolution_clock::time_point end;

    vector<int> Z = v;
    start = chrono::high_resolution_clock::now();
    Z = sortFunc(Z);
    end = chrono::high_resolution_clock::now();

    double elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();

    std::cout << (isSorted(Z) ? "Sorting successful\n" : "Sorting failed\n");
    //printVector(Z);
    //cout << "\nElapsed time: " << elapsed << endl;
    return elapsed;
}

vector<double> calculateTime(const vector<double> &v)
{
    // <Min, Mean, StdDev, Max

    vector<double> timeOutliers;

    double minimum = v[0];
    double maximum = v[0];
    double sum = 0;

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

int main()
{
    std::ofstream file("timings.csv");

    srand(time(NULL));

    vector<vector<int>> list;
    vector<vector<int>> copies;

    for(int i = 0; i < 10; i++)
    {
        list.push_back(randomVector(1000, -10000, 10000));
        //personalTest(list[i]);
    }

    vector<double> timeValues;
    vector<double> timeOutliers;
    bool sorted = false;

    // MAKE A VECTOR OF COPIES OF VECTORS ABOVE, MAY HELP WITH SORTING SUCCESSFUL OUTPUT, WILL ALLOW ME TO ACTUALLY SORT THE PASSED VECTOR SO I CAN CHECK THAT VECTOR ALONE INSTEAD OF A COPY

    std::cout << "*************************" << std::endl;
    std::cout << "Bubble sort on 10 vectors of length " << list[0].size() << std::endl;
    for(int i = 0; i < list.size(); i++)
    {
        // printVector(list[i]);
        double bubble = timeSort(list[i], bubbleSort);
        timeValues.push_back(bubble);
        file << "Bubble" << ", " << list[i].size() << ", " << bubble << std::endl;
    }
    timeOutliers = calculateTime(timeValues);
    std::cout << "Minimum: " << timeOutliers[0] << "; Mean: " << timeOutliers[1] << "; Standard Deviation: " << timeOutliers[2] << "; Maximum: " << timeOutliers[3] << std::endl;
    timeValues.clear();
    timeOutliers.clear();

    std::cout << std::endl;
    std::cout << "*************************\n" << std::endl;

    std::cout << "*************************" << std::endl;
    std::cout << "Insertion sort on 10 vectors of length " << list[0].size() << std::endl;
    for(int i = 0; i < list.size(); i++)
    {
        // printVector(list[i]);
        double insertion = timeSort(list[i], insertionSort);
        timeValues.push_back(insertion);
        file << "Insertion" << ", " << list[i].size() << ", " << insertion << std::endl;
    }
    timeOutliers = calculateTime(timeValues);
    std::cout << "Minimum: " << timeOutliers[0] << "; Mean: " << timeOutliers[1] << "; Standard Deviation: " << timeOutliers[2] << "; Maximum: " << timeOutliers[3] << std::endl;
    timeValues.clear();
    timeOutliers.clear();

    std::cout << std::endl;
    std::cout << "*************************\n" << std::endl;

    std::cout << "*************************" << std::endl;
    std::cout << "Selection sort on 10 vectors of length " << list[0].size() << std::endl;
    for(int i = 0; i < list.size(); i++)
    {
        // printVector(list[i]);
        double selection = timeSort(list[i], selecionSort);
        timeValues.push_back(selection);
        file << "Selection" << ", " << list[i].size() << ", " << selection << std::endl;
    }
    timeOutliers = calculateTime(timeValues);
    std::cout << "Minimum: " << timeOutliers[0] << "; Mean: " << timeOutliers[1] << "; Standard Deviation: " << timeOutliers[2] << "; Maximum: " << timeOutliers[3] << std::endl;
    timeValues.clear();
    timeOutliers.clear();

    std::cout << std::endl;
    std::cout << "*************************\n" << std::endl;

    std::cout << "*************************" << std::endl;
    std::cout << "Quick sort on 10 vectors of length " << list[0].size() << std::endl;
    for(int i = 0; i < list.size(); i++)
    {
        // printVector(list[i]);
        double quick = timeSort(list[i], quickSort);
        timeValues.push_back(quick);
        file << "Quick" << ", " << list[i].size() << ", " << quick << std::endl;
    }
    timeOutliers = calculateTime(timeValues);
    std::cout << "Minimum: " << timeOutliers[0] << "; Mean: " << timeOutliers[1] << "; Standard Deviation: " << timeOutliers[2] << "; Maximum: " << timeOutliers[3] << std::endl;
    timeValues.clear();
    timeOutliers.clear();
    
    std::cout << std::endl;
    std::cout << "*************************\n" << std::endl;

    file.close();

    return 0;
};