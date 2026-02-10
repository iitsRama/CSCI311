// Lab 2 Skeleton
// Author: Amar Bulic, ID: 013040249

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;


/*************************************************************
 * Your solutions go below here and do not change the headers*
 * ***********************************************************/

 // Calculates the number of points required to construct a triangle with n dots recursively
int triangleNum(int n)
{
  // if n > 0 return n + triangleNum(n-1) (recursive call), else return 0
  // essentially acts as a while loop, adding n + n-1 + n-2 until 0, 
  return (n > 0) ? n + triangleNum(n - 1) : 0;
}

// Calculates the nth fibonnacci number
int rFib(int n)
{
  // if n <= 1 return n, else return rFib(n-1) + rFib(n-2)
  // for n <= 1, result will be itself. 
  // for all other cases, return Fib(n-1) + Fib(n-2), this is the nth number of the sequence for any n > 1
  return (n <= 1) ? n : (rFib(n - 1) + rFib (n - 2));
}

// Helper function which allows us to actually index our vector while maintaining recursion
int rSumHelper(const vector<int> &v, int i)
{
  // if i < size return v[i] + (v[i + 1] + (v[i+2])) ... = sum of all elements of vector, else return 0
  return (i < v.size()) ? v[i] + rSumHelper(v, i + 1) : 0; 
}

// Calculates the sum of all elements in a given vector v
int rSum(const vector<int> &v)
{
  // Passes vector and index 0 to helper function, returns that result
  return rSumHelper(v, 0);
}

// Helper function, allows us to iterate through our vector recursively 
int rMaxHelper(const vector<int> &v, int start)
{
  if(v.size() == 0) { return INT_MIN; }

  // if size != 0, index < size, index >= 0
  else if(start < v.size() && start >= 0)
  {
    //return max between v[0], (v[1], (v[2], v[3] ....)  until end is reached, will give max value
    return max(v[start],rMaxHelper(v, start + 1));
  }

  else { return 0; }
}

// Finds the max value in a list using recursion
int rMax(const vector<int> &v)
{
  // passes vector and starting index of 0 to helper function
  return rMaxHelper(v, 0);
}

// Checks if a list is sorted using recursion
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

// Helper function that allows us to iterate through our passed string
bool isPalindromeHelper(string s, int start, int end)
{
  // if size is 0 or 1, is guaranteed palindrome.
  // if start > end, false case never triggered.
  if(s.size() == 0 || s.size() == 1 || start > end) { return true ; }

  //checks all cases by checking s[start] against s[end], then incrementing start and decrementing end until they meet or pass each other
  else
  {
    // if s[i=0] = s[n], check s[i=1] against s[n-1], until i = n - k, else return false if they dont match
    return (s[start] == s[end]) ? isPalindromeHelper(s, start + 1, end - 1) : false;
  }
}

// Recursively checks if passed string is a palindrome, same forward as backwards, eg. racecar
bool isPalindrome(string s)
{
  //passes values: string s, start = 0, end = length - 1
  return isPalindromeHelper(s, 0, s.length() - 1);
}

// recursive binary search through a list. Will use recursion to split list in half until target is found, or returns -1
int rBinarySearch(const vector<int> &v, int low, int high, int target)
{
  // if size = 0 or start index > end index (will happen when target not found, indices will pass each other), return -1
  if(v.size() == 0 || low > high) { return -1; }
  // set middle of array to average = low + high / 2
  int middle = (low + high) / 2;
  // if target found, return index
  if(v[middle] == target) { return middle; }
  // else if middle < target, set new low = middle + 1, high = high.
  // if middle > target, set low = low, new high = middle - 1. 
  // This will check every value and keep splitting list until target found or exit case reached
  return(v[middle] < target) ? rBinarySearch(v, middle + 1, high, target) : rBinarySearch(v, low, middle - 1, target);
}

// Helper for Subset calculation. Passes vector, start value, target value, and a sum variable to track if subset is possible.
bool rSubsetHelper(const vector<int> &v, int start, int target, int sum)
{
  // if sum reaches target, there is a subset that sums to the target.
  if(sum == target) { return true; }
  // if i reaches size, not possible, return false
  if(start == v.size()) { return false; }
  // else check two cases:
  // we want to check all subsets of v. So we will have to check each next value either including or not including the next value
  // eg. [0.1.2.3] -> check 0, check 0+1: 0+1+2... check 0+2: 0+2, 0+2+3... check 0+3: 0+3.... until all subsets checked
  // therefor, recursive call will either check the nth number or skip it
  else
  {
    return rSubsetHelper(v, start + 1, target, sum + v[start]) || rSubsetHelper(v, start + 1, target, sum); 
  }
}

// Checks to see if a subset of a passed vector will sum to target number
bool rSubsetSum(const vector<int> &v, int start, int target)
{
  // passes v, start = 0, target number, sum = 0
  return rSubsetHelper(v, 0, target, 0);
}

/***********************************************
 * Main and helper functions for quick testing *
 * *********************************************/
void readIntVector(vector<int> &v, int n);

int main(){
  int question = -1;
  cout << "Question: ";
  cin >> question;

  int n = 0, start = 0, end = 0;
  vector<int> v;
  string s = "";
  switch (question){
    case 1: //triangleNum
      cout << "Triangle Number n: ";
      cin >> n;
      cout << triangleNum(n) << endl;
      break;
    case 2: //rFib
      cout << "Nth Fibonacci Number: ";
      cin >> n;
      cout << rFib(n) << endl;
      break;
    case 3: //rSum
      cout << "Recursive Sum Vector Size: ";
      cin >> n;
      cout << "Values: ";
      readIntVector(v, n);
      cout << rSum(v) << endl;
      break;
    case 4: //rMax
      cout << "Recursive Max Vector Size: ";
      cin >> n;
      cout << "Values: ";
      readIntVector(v, n);
      cout << rMax(v) << endl;
      break;
    case 5: //isSorted
      cout << "isSorted Vector Size: ";
      cin >> n;
      cout << "Start and End: ";
      cin >> start >> end;
      cout << "Values: ";
      readIntVector(v, n);
      cout << isSorted(v, start, end) << endl;
      break;
    case 6: //isPalindrome
      cout << "String: ";
      cin >> s;
      cout << isPalindrome(s) << endl;
      break;
    case 7: //rBinarySearch
      cout << "Binary Search Vector Size: ";
      cin >> n;
      cout << "Target: ";
      cin >> end;
      cout << "Values: ";
      readIntVector(v, n);
      cout << rBinarySearch(v, 0, v.size()-1, end) << endl;
      break;
    case 8: //rSubsetSum
      cout << "Subset Sum Vector Size: ";
      cin >> n;
      cout << "Target: ";
      cin >> end;
      cout << "Values: ";
      readIntVector(v, n);
      cout << rSubsetSum(v, 0, end) << endl;
      break;
  }

  return 0;
}

/**************************************************
 * Read a vector of integers in from cin          *
 * v - vector<int> & - the integer vector to fill *
 * n - int - the number of integers to read       *
 * ************************************************/
void readIntVector(vector<int> &v, int n){
  int m = 0;
  for (int i = 0; i < n; i++){
    cin >> m;
    v.push_back(m);
  }
}
