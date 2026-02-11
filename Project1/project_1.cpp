#include <iostream>
using namespace std;
#include <vector>
#include <time.h>
#include <math.h>
#include <chrono>
#include <fstream>

// bool isSorted(const vector<int> &v, int start, int end)
// {
//   // if start index >= end index, size <= 1, return true. 
//   // size 0 and 1 vector will always be sorted
//   // if start index reaches end index, false case never triggered, therefor must be sorted.
//   if(start >= end || v.size() == 1 || v.size() == 0) { return true; }

//   // Checks all cases, only if no case returns false does the above if statement trigger
//   else
//   {
//     // if v[i] <= v[i+1], or if v in ascending order for those two indices, test [i+1] against [i+2] until i reaches end value
//     // return false if any v[i-1] > v[i];
//     return (v[start] <= v[start + 1]) ? isSorted(v, start + 1, end) : false;
//   }
// }

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
    std::cout << v[v.size()] << "}" << std::endl;
}

// void runSorts(const std::string& name, const std::vector<int>& v)
// {
//     std::cout << name << ": " << v.size() << " elements" << std::endl;

//     std::vector<int> Z;

//     Z = v;
//     std::cout << "ORIGINAL  - " << Z.size() << ": ";
//     printVector(Z);

//     Z = v;
//     bubbleSort(Z);
//     std::cout << "BUBBLE    - " << Z.size() << ": ";
//     printVector(Z);
//     std::cout << "  sorted? " << (isSorted(Z, 0, Z.size() - 1) ? "YES" : "NO") << std::endl;

//     Z = v;
//     insertionSort(Z);
//     std::cout << "INSERTION - " << Z.size() << ": ";
//     printVector(Z);
//     std::cout << "  sorted? " << (isSorted(Z, 0, Z.size() - 1) ? "YES" : "NO") << std::endl;

//     Z = v;
//     selecionSort(Z);
//     std::cout << "SELECTION - " << Z.size() << ": ";
//     printVector(Z);  
//     std::cout << "  sorted? " << (isSorted(Z, 0, Z.size() - 1) ? "YES" : "NO") << std::endl;

//     Z = v;
//     quickSort(Z);
//     std::cout << "QUICK     - " << Z.size() << ": ";
//     printVector(Z);
//     std::cout << "  sorted? " << (isSorted(Z, 0, Z.size() - 1) ? "YES" : "NO") << std::endl;
// }

// void personalTest(const vector<int> &v)
// {
//     runSorts("A", v);
// }



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

double timeSort(vector<int> &v, std::vector<int> (*sortFunc)(std::vector<int>&))
{
    chrono::high_resolution_clock::time_point start;
    chrono::high_resolution_clock::time_point end;

    vector<int> Z = v;
    start = chrono::high_resolution_clock::now();
    Z = sortFunc(Z);
    end = chrono::high_resolution_clock::now();

    double elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();

    std::cout << (isSorted(Z) ? "Sorting successful" : "Sorting failed");
    //printVector(Z);
    cout << "\nElapsed time: " << elapsed << endl;
    return elapsed;
}

// void classTest(vector<int> &v, std::vector<int> (*sortFunc)(std::vector<int>&))
// {
//     vector<double> runTimes;
//     runTimes.push_back(timeSort(v, sortFunc));
// }

int main()
{
    std::ofstream file("timings.csv");

    srand(time(NULL));

    vector<vector<int>> List;

    for(int i = 0; i < 10; i++)
    {
        List.push_back(randomVector(10000, -1000, 1000));
        //personalTest(List[i]);
    }

    std::cout << "*************************" << std::endl;
    std::cout << "Bubble sort on 10 vectors of length " << List[0].size() << std::endl;
    for(int a = 0; a < List.size(); a++)
    {
        double bubble = timeSort(List[a], bubbleSort);
        file << "Bubble" << ", " << List[a].size() << ", " << bubble << std::endl;
    }
    std::cout << std::endl;
    std::cout << "*************************\n" << std::endl;

    std::cout << "*************************" << std::endl;
    std::cout << "Insertion sort on 10 vectors of length " << List[0].size() << std::endl;
    for(int a = 0; a < List.size(); a++)
    {
        double insertion = timeSort(List[a], insertionSort);
        file << "Insertion" << ", " << List[a].size() << ", " << insertion << std::endl;
    }
    std::cout << std::endl;
    std::cout << "*************************\n" << std::endl;

    std::cout << "*************************" << std::endl;
    std::cout << "Selection sort on 10 vectors of length " << List[0].size() << std::endl;
    for(int a = 0; a < List.size(); a++)
    {
        double selection = timeSort(List[a], selecionSort);
        file << "Selection" << ", " << List[a].size() << ", " << selection << std::endl;
    }
    std::cout << std::endl;
    std::cout << "*************************\n" << std::endl;

    std::cout << "*************************" << std::endl;
    std::cout << "Quick sort on 10 vectors of length " << List[0].size() << std::endl;
    for(int a = 0; a < List.size(); a++)
    {
        double quick = timeSort(List[a], quickSort);
        file << "Quick" << ", " << List[a].size() << ", " << quick << std::endl;
    }
    std::cout << std::endl;
    std::cout << "*************************\n" << std::endl;

    file.close();

    return 0;
};