#include <iostream>
using namespace std;
#include <vector>
#include <ctime>

bool isSorted(const vector<int> &v, int start, int end)
{
  // if start index >= end index, size <= 1, return true. 
  // size 0 and 1 vector will always be sorted
  // if start index reaches end index, false case never triggered, therefor must be sorted.
  if(start >= end || v.size() == 1 || v.size() == 0) { return true; }

  // Checks all cases, only if no case returns false does the above if statement trigger
  else
  {
    // if v[i] <= v[i+1], or if v in ascending order for those two indices, test [i+1] against [i+2] until i reaches end value
    // return false if any v[i-1] > v[i];
    return (v[start] <= v[start + 1]) ? isSorted(v, start + 1, end) : false;
  }
}

vector<int> bubbleSort(vector<int> &v)
{
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
    for(int i = 1; i < v.size(); i++)
    {
        for(int j = 1; j > 0 && v[i] < v[i-1]; j--)
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
    if( v.size() <= 1)
    {
        return v;
    }

    int pivot = v[0];
    vector<int> A = {};
    vector<int> B = {};
    for(int i = 1; i < v.size(); i++)
    {
        if(v[i] <= pivot)
        {
            A.push_back(v[i]);
            quickSort(A);
        }
        else
        {
            B.push_back(v[i]);
            quickSort(B);
        }
    }

    vector<int> C = A;
    C.push_back(pivot);
    for(int j = 0; j < B.size(); j++)
    {
        C.push_back(B[j]);
    }

    return C;
}

void printVector(const vector<int> v)
{
    std::cout << "{";
    for(int i = 0; i < v.size() - 1; i++)
    {
        std::cout << v[i] << ", ";
    }
    std::cout << v[v.size() - 1] << "}" << std::endl;
}

// void test()
// {
//     vector<int> A = {8,6,3,10,9,1,14,15,7};                 // 9 elements
//     vector<int> B = {14, 7, 5, 3, 9, 6, 1, 13, 55, 9, 0};   // 11 elements
//     vector<int> C = {1,2,3,4,5,6,7,8,9};                    // 9 elements
//     vector<int> D = {20,19,18,17,16,15,14,13};              // 8 elements
//     vector<int> E = {1};                                    // 1 element
//     vector<int> F = {};                                     // 0 elements

//     if(!isSorted(A, 0, A.size()))
//     {
//         std::cout << "A:" << std::endl;

//         vector<int> Z = A;
//         std::cout << "ORIGINAL: ";
//         printVector(Z);

//         bubbleSort(Z);
//         std::cout << "BUBBLE: ";
//         printVector(Z);

//         Z = A;
//         insertionSort(Z);
//         std::cout << "INSERTION: ";
//         printVector(Z);

//         Z = A;
//         selecionSort(Z);
//         std::cout << "SELECTION: ";
//         printVector(Z);

//         Z = A;
//         quickSort(Z);
//         std::cout << "QUICK: ";
//         printVector(Z);
//     }
//     if(!isSorted(B, 0, B.size()))
//     {
//         std::cout << "B:" << std::endl;

//         vector<int> Z = B;
//         std::cout << "ORIGINAL: ";
//         printVector(Z);

//         bubbleSort(Z);
//         std::cout << "BUBBLE: ";
//         printVector(Z);

//         Z = B;
//         insertionSort(Z);
//         std::cout << "INSERTION: ";
//         printVector(Z);

//         Z = B;
//         selecionSort(Z);
//         std::cout << "SELECTION: ";
//         printVector(Z);
        
//         Z = B;
//         quickSort(Z);
//         std::cout << "QUICK: ";
//         printVector(Z);
//     }
//     if(!isSorted(C, 0, C.size()))
//     {
//         std::cout << "C:" << std::endl;

//         vector<int> Z = C;
//         std::cout << "ORIGINAL: ";
//         printVector(Z);

//         bubbleSort(Z);
//         std::cout << "BUBBLE: ";
//         printVector(Z);

//         Z = C;
//         insertionSort(Z);
//         std::cout << "INSERTION: ";
//         printVector(Z);

//         Z = C;
//         selecionSort(Z);
//         std::cout << "SELECTION: ";
//         printVector(Z);
        
//         Z = C;
//         quickSort(Z);
//         std::cout << "QUICK: ";
//         printVector(Z);
//     }
//     if(!isSorted(D, 0, D.size()))
//     {
//         std::cout << "D:" << std::endl;

//         vector<int> Z = D;
//         std::cout << "ORIGINAL: ";
//         printVector(Z);

//         bubbleSort(Z);
//         std::cout << "BUBBLE: ";
//         printVector(Z);

//         Z = D;
//         insertionSort(Z);
//         std::cout << "INSERTION: ";
//         printVector(Z);

//         Z = D;
//         selecionSort(Z);
//         std::cout << "SELECTION: ";
//         printVector(Z);
        
//         Z = D;
//         quickSort(Z);
//         std::cout << "QUICK: ";
//         printVector(Z);
//     }
//     if(!isSorted(E, 0, E.size()))
//     {
//         std::cout << "E:" << std::endl;

//         vector<int> Z = E;
//         std::cout << "ORIGINAL: ";
//         printVector(Z);

//         bubbleSort(Z);
//         std::cout << "BUBBLE: ";
//         printVector(Z);

//         Z = E;
//         insertionSort(Z);
//         std::cout << "INSERTION: ";
//         printVector(Z);

//         Z = E;
//         selecionSort(Z);
//         std::cout << "SELECTION: ";
//         printVector(Z);
        
//         Z = E;
//         quickSort(Z);
//         std::cout << "QUICK: ";
//         printVector(Z);
//     }
//     if(!isSorted(F, 0, F.size()))
//     {
//         std::cout << "F:" << std::endl;

//         vector<int> Z = F;
//         std::cout << "ORIGINAL: ";
//         printVector(Z);

//         bubbleSort(Z);
//         std::cout << "BUBBLE: ";
//         printVector(Z);

//         Z = F;
//         insertionSort(Z);
//         std::cout << "INSERTION: ";
//         printVector(Z);

//         Z = F;
//         selecionSort(Z);
//         std::cout << "SELECTION: ";
//         printVector(Z);
        
//         Z = F;
//         quickSort(Z);
//         std::cout << "QUICK: ";
//         printVector(Z);
//     }
// }


void runOne(const std::string& name, const std::vector<int>& input)
{
    auto checkSort = [&](const std::string& algName, auto sorter) {
        std::vector<int> z = input;

        sorter(z);

        if (!isSorted(z, 0, z.size())) { // adjust if your isSorted uses inclusive end
            std::cout << name << " FAILED " << algName << "\n";
            std::cout << "ORIGINAL: "; printVector(input);
            std::cout << "RESULT:   "; printVector(z);
        }
    };

    checkSort("BUBBLE",    [](auto& v){ bubbleSort(v); });
    checkSort("INSERTION", [](auto& v){ insertionSort(v); });
    checkSort("SELECTION", [](auto& v){ selecionSort(v); });
    checkSort("QUICK",     [](auto& v){ quickSort(v); });
}

void test()
{
    runOne("A", {8,6,3,10,9,1,14,15,7});
    runOne("B", {14, 7, 5, 3, 9, 6, 1, 13, 55, 9, 0});
    runOne("C", {1,2,3,4,5,6,7,8,9});
    runOne("D", {20,19,18,17,16,15,14,13});
    runOne("E", {1});
    runOne("F", {});
}


int main()
{
    test();

    return 0;
}