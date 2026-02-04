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
  // Break case for recursive call
  // When triangleNum(n-1) called, n = n-1, n - 1 = n - 2, etc, etc. When n = 0 is reached, it will return backwards from the lowest number n - x
  //      to n, summing them all up
  return (n > 0) ? n + triangleNum(n - 1) : 0;
}

int rFib(int n)
{
  // if n <= 1 return n, else return rFib(n-1) + rFib(n-2)
  return (n <= 1) ? n : (rFib(n - 1) + rFib (n - 2));
}

int rSumHelper(const vector<int> &v, int i)
{
  return (i < v.size()) ? v[i] + rSumHelper(v, i + 1) : 0; 
}

int rSum(const vector<int> &v)
{
  return rSumHelper(v, 0);
}

int rMaxHelper(const vector<int> &v, int start)
{
  if(v.size() == 0) { return INT_MIN; }

  else if(start < v.size() && start >= 0)
  {
    return max(v[start],rMaxHelper(v, start + 1));
  }

  else { return 0; }
}

int rMax(const vector<int> &v)
{
  return rMaxHelper(v, 0);
}

bool isSorted(const vector<int> &v, int start, int end)
{
  if(start >= end || v.size() == 1 || v.size() == 0) { return true; }

  else
  {
    return (v[start] <= v[start + 1]) ? isSorted(v, start + 1, end) : false;
  }
}

bool isPalindromeHelper(string s, int start, int end)
{
  if(s.size() == 0 || s.size() == 1 || start > end) { return true ; }

  else
  {
    return (s[start] == s[end]) ? isPalindromeHelper(s, start + 1, end - 1) : false;
  }
}

bool isPalindrome(string s)
{
  return isPalindromeHelper(s, 0, s.length() - 1);
}

int rBinarySearch(const vector<int> &v, int low, int high, int target)
{
  if(v.size() == 0 || low > high) { return -1; }
  int middle = (low + high) / 2;
  if(v[middle] == target) { return middle; }
  return(v[middle] < target) ? rBinarySearch(v, middle + 1, high, target) : rBinarySearch(v, low, middle - 1, target);
}

bool rSubsetHelper(const vector<int> &v, int start, int target, int sum)
{
  if(sum == target) { return true; }
  if(start == v.size()) { return false; }
  else
  {
    return rSubsetHelper(v, start + 1, target, sum + v[start]) || rSubsetHelper(v, start + 1, target, sum); 
  }
}

bool rSubsetSum(const vector<int> &v, int start, int target)
{
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
