// Author:
// Amar Bulic
// CSU Chico ID # 013040249

#include <iostream>
using namespace std;
#include <vector>
#include <time.h>
#include <math.h>
#include <chrono>
#include <fstream>

// Checks if passed vector is sorted in ascending order.
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

// Bubble sort, checks v[n-1] against v[n] for all n belonging to v.
void bubbleSort(vector<int> &v)
{
    // size 1 or empty is always sorted
    if (v.size() < 2) { return; }

    bool sorted = false;

    while(!sorted)
    {
        // Assume sorted = true, then if belong set to false so while loop iterates
        sorted = true;

        for(int i = 1; i < v.size(); i++)
        {
            // If last index > current index, swap them
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

// Insertion sort, separates vector into 2 parts, sorted and unsorted part. Checks first value of unsorted against all sorted values, then inserts where proper.
void insertionSort(vector<int> &v)
{
    if (v.size() < 2) { return; }

    // Increment inner loop start index, this is what separates insertion sort from bubble sort.
    for(int i = 1; i < v.size(); i++)
    {
        // If current index < previous index, swap current index left. 
        for(int j = i; j > 0 && v[j] < v[j-1]; j--)
        {
            int temp = v[j-1];
            v[j-1] = v[j];
            v[j] = temp;
        }
    }
}

// Selection sort, find minimum value and swap into place.
void selectionSort(vector<int> &v)
{
    if (v.size() < 2) { return; }

    // Increment inner loops start index.
    for(int i = 0; i < v.size() - 1; i++)
    {
        int uMin = i;
        
        // Inner loop will find smallest value.
        for(int j = i + 1; j < v.size(); j++)
        {
            if(v[j] < v[uMin])
            {
                uMin = j;
            }
        }
        
        // Set smallest value to v[i], or the correct ascending order place.
        int temp = v[i];
        v[i] = v[uMin];
        v[uMin] = temp;
    }
}

// Quick sort, index 0 is pivot, int i and j chosen as [1] and [size - 1], increment i and decrement j until i > pivot, j < pivot, swap those values, repeat.
// when i > j, break out of above loop, swap pivot with j, then recursive call to sort the left and right halves of the list.
void quickSortHelper(vector<int>&v, int low, int high)
{
    // Base case, when indices reach each other as start values
    if (low >= high) return;

    int pivot = v[low];
    int i = low + 1;
    int j = high;

    while (true)
    {
        // i <= j ensures no out of bounds
        // increment i and check against pivot value, stop when > pivot
        // increment j and check agains tpivot value, stop when <= pivot
        while (i <= j && v[i] <= pivot) { i++; }
        while (i <= j && v[j] > pivot) { j--; }

        // When indices pass each other, or when i passes j, leave loop
        if(i > j) { break; }

        // Swap v[i] & v[j]
        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
    }

    // Swap pivot with j, j ends at last element <= pivot
    int temp = v[low];
    v[low] = v[j];
    v[j] = temp;

    // Recursion on sub arrays, left and right from pivot
    quickSortHelper(v, low, j - 1);
    quickSortHelper(v, j + 1, high);
}

// Quick sort container that allows us to use function pointers below. Calls quicksorthelper.
void quickSort(vector<int> &v)
{
    int low = 0;
    int high = v.size() - 1;
    quickSortHelper(v, low, high);
}

// Same as above quick sort, but our pivot value is the median value of the entire list.
void bestQuickSortHelper(vector<int> &v, int low, int high)
{
    // Base case, when indices reach each other as start values
    if (low >= high) return;

    // Median value of list, only works if list is sorted.
    int mid = (low + high) / 2;

    // Swap mid value to first value of list. This allows us to avoid creating an overloaded function of runTests below
    // and instead allows us to call our quickSortHelper above.
    int tmp = v[low];
    v[low] = v[mid];
    v[mid] = tmp;

    quickSortHelper(v, low, high);
}

void bestQuickSort(vector<int> &v)
{
    int low = 0;
    int high = v.size() - 1;
    bestQuickSortHelper(v, low, high);
}

// Calculate the sample standard deviation of a vector of doubles
// v - const vector<double> - a vector of doubles
// return - double - the sample standard deviation of v
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

// Measures time taken to sort a vector.
// void (*sortFunc)(std::vector<int>&) is a pointer to a function which returns void and takes a reference to a vector of integers as an argument
// This allows us to write just one timing function, and pass different sorting functions to it.
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

// Takes a vector of doubles, or time values, and returns the minimum, mean, standard deviation, and maximum values.
vector<double> calculateTime(const vector<double> &v)
{
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

// Processes data
// passing list by value makes a copy, lets me modify list all I want
// sortName, file used to organize data in their respective .csv files
// list is a vector of vectors
// same function pointer as above, allows use of separate sorts.
void processData(std::string sortName, vector<vector<int>> list, std::ofstream &file, void (*sortFunc)(std::vector<int>&))
{
    vector<double> timeValues;
    vector<double> timeOutliers;
    bool sorted = true;

    // Sort all the vector in list, calculate the time it took, push that time into an array, and write to .csv
    for(int i = 0; i < list.size(); i++)
    {
        double timeValue = timeSort(list[i], sortFunc);
        timeValues.push_back(timeValue);
        file << sortName << "," << list[i].size() << "," << timeValue << std::endl;
    }
}

// Overloaded version of above function to accommodate base output to command line that assignment desires. 
// Outputs to console based on 10 arrays of size 100
// Outputs Min, Mean, StdDev, and Max time taken
void processData(std::string sortName, vector<vector<int>> list, void (*sortFunc)(std::vector<int>&))
{
    vector<double> timeValues;
    vector<double> timeOutliers;
    bool sorted = true;

    std::cout << "================================================\n" << std::endl;
    std::cout << sortName << " sort on " << list.size() << " vectors of length " << list[0].size() << std::endl;
    for(int i = 0; i < list.size(); i++)
    {
        double timeValue = timeSort(list[i], sortFunc);
        timeValues.push_back(timeValue);
        sorted = sorted && isSorted(list[i]);
    }

    (sorted) ? std::cout << "Sorting successful\n" : std::cout <<  "Sorting failed\n";
    
    timeOutliers = calculateTime(timeValues);

    std::cout << "Minimum: " << timeOutliers[0] << "; Mean: " << timeOutliers[1] << "; Standard Deviation: " << timeOutliers[2] << "; Maximum: " << timeOutliers[3] << std::endl;
    std::cout << std::endl;
    std::cout << "================================================\n"<< std::endl;
}

// Generate a vector of random integers in a given range. The ends
// of this range are inclusive.
// size - int - the number of integers in the resulting vector
// low, high - int - the range from which to draw random integers (inclusive)
// return - vector<int> - a vector of random integers
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

// Generate a specified amount of ascending sorted vectors of size size, ranging from [low, high].
vector<vector<int>> sortedVector(int size, int low, int high, int amount)
{
    vector<vector<int>> list;
    vector<int> v(size);

    for(int i = 0; i < amount; i++)
    {
        // Set range as [low : high - size - 1], so we stay in bounds.
        int start = low + rand() % (high - low - (size - 1) + 1);
        for(int j = 0; j < size; j++)
        {
            v[j] = start + j;
        }
        list.push_back(v);
    }

    return list;
}

// Generate a specified amount of descending sorted vectors of size size, ranging from [low, high]
vector<vector<int>> reverseSortedVector(int size, int low, int high, int amount)
{
    vector<vector<int>> list;
    vector<int> v(size);

    for(int i = 0; i < amount; i++)
    {
        // Set start value as [high - (high - low - (size - 1)) : high] ensures reverse sorted vector that is in bounds.
        // Ex.) if size = 1000, high value = 10000, range is [999 : 10000] -> rand % 9002 = 0, 1, 2, ... , 9001; high - 9001 = 999
        int start = high - rand() % (high - low - (size - 1) + 1);
        for(int j = 0; j < size; j++)
        {
            v[j] = start - j;
        }
        list.push_back(v);
    }

    return list;
}

// Generate a specified amount of vectors ranging from [low, high]
// Special case for the worst case run time of selection sort
// vector will be ascending even numbers until size / 2 is reached, then will swap to descending odd numbers for the remaining space
// Passed int high not used, as it would require an overload of one of the data functions below. This keeps it inline with the other 
// vector generating functions.
vector<vector<int>> worstSelectionVector(int size, int low, int high, int amount)
{
    vector<vector<int>> list;
    list.reserve(amount);

    for(int i = 0; i < amount; i++)
    {
        int half = size / 2;

        // Find step value, this will enable the pattern ascending even values -> descending odd values, within range, evenly spaced.
        int difference = high / half;
        
        // Ensure step is an even number
        if (difference % 2 != 0) difference++; 

        vector<int> v(size);

        int ascending = low;

        // Starting at high - 1 allows us to keep difference at an even value, and will always give us an odd result when subtracting.
        int descending  = high - 1;

        // first half: ascending evens
        for(int j = 0; j < size/2; j++)
        {
            v[j] = ascending;
            ascending += difference;
        }

        // second half: descending odds
        for(int k = size/2; k < size; k++)
        {
            v[k] = descending;
            descending -= difference;
        }

        list.push_back(v);
    }

    return list;
}

// Main function call, will take a vector of vectors, the low and high values specified in main, the amount of vectors desired,
// the file for which to write data, the sort function you wish to test, the name of that sort function, and a case name for switch case
void runTests(vector<vector<int>> &v, int low, int high, int amount, std::ofstream &file,
                void (*sortFunc)(std::vector<int>&), std::string sortName, char caseName)
{
    // All list sizes tested.
    std::vector<int> sizes = {100, 200, 400, 800, 1600, 3200, 6400, 12800};

    for(int i = 0; i < sizes.size(); i++)
    {
        // For desired size, generate a vector according to the case name char passed
        switch(caseName)
        {
            // Best case
            case 'b':
                v = sortedVector(sizes[i], low, high, amount);
                break;
            // Average case
            case 'a':
                v = randomVector(sizes[i], low, high, amount);
                break;
            // Worst case
            case 'w':
                v = reverseSortedVector(sizes[i], low, high, amount);
                break;
            // Worst case for selection sort
            case 's':
                v = worstSelectionVector(sizes[i], low, high, amount);
                break;
            default:
                return;
        }
        // Pass that vector and the previously passed sorting function to process data function, along with the name of the sort and the file.
        processData(sortName, v, file, sortFunc);
    }
}

// Overloaded version of above function, allows us to pass the same arguments except for the file, so that we can output the base case to console
// without writing to a file. Used for question 2.1
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

    processData(sortName, v, sortFunc);
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

    // #2.1 on project sheet
    runTests(v, low, high, 10, bubbleSort, "Bubble", 'a');
    runTests(v, low, high, 10, insertionSort, "Insertion", 'a');
    runTests(v, low, high, 10, selectionSort, "Selection", 'a');
    runTests(v, low, high, 10, quickSort, "Quick", 'a');

    // Main data set
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

// Prints out entire vector, used for debugging.
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