// CSCI 311
// Lab 1 Skeleton
// Author: Carter Tillquist

#include <iostream>
#include <math.h>
#include <chrono>
#include <vector>
using namespace std;

/*************************************************************
 * Your solutions go below here and do not change the headers*
 * ***********************************************************/

// Amar Bulic
// 013040249

// given any integer n, if n is even: n/2, if n id odd: 3n+1, until n = 1, return # of steps
int collatzLength(int n){

  // make sure n is not 0
  if(n == 0) { return 0; }

  // initiate variable to count number of steps
  int count = 0;

  // while |n| != 1; this ensures negative numbers are also allowed.
  while(abs(n) != 1)
  {
    // if n is even n = n/2, increase count
    if(n % 2 == 0)
    {
      n /= 2;
      count++;
    }
    // else n must be odd. n = 3n+1, increase count
    else
    {
      n = (3 * n) + 1;
      count++;
    }
  }

  return count;
}

// given a vector v, print the minimum, maximum, and mean values
void printStats(const vector<int> &v)
{
  // if v is empty, cout empty vector
  if(v.empty()) 
  {
    std::cout << "Empty vector" << std::endl;
    return;
  }

  //  set all values to first element of v
  int minimum = v.front();
  int maximum = v.front();
  float sum = v.front();
  
  // loop through v, start at 1 since we already have the first element set to all variables
  for(int i = 1; i < v.size(); i++)
  {
    // calculate sum to allow mean calculation
    sum += v[i];

    // if current element > max, set max = current element
    if(v[i] > maximum)
    {
      maximum = v[i];
    }
    // if current element < min, set min = current element
    if(v[i] < minimum)
    {
      minimum = v[i];
    }
  }

  // calculate mean by dividing sum by size of vector
  float mean = sum / (v.size());

  std::cout << minimum << " " << mean << " " << maximum << std::endl;
}

// calculates the sum of all multiples of elements in vector v
int sumMultiples(const vector<int> &v, int n)
{
  if(v.empty()) { return 0; }

  // initialize sum variable and a temporary vector to hold all multiples
  int sum = 0;
  vector<int> multiples;

  // loop through v
  for(int i = 0; i < v.size(); i++)
  {
    // value = current value
    int value = v[i];

    // calculate, sum, and add to vector the multiples of the current value
    for(int tempVal = value; tempVal < n; tempVal += value)
    {
      // boolean flag allows us to track duplicates
      bool duplicate = false;

      // loop through temp val checking for duplicates
      for(int j = 0; j < multiples.size(); j++)
      {
        // if duplicate, set boolean flag true, break
        if(multiples[j] == tempVal)
        {
          duplicate = true;
          break;
        }
      }

      // if not duplicate, push value to multiples vector, append sum
      if(!duplicate)
      {
        multiples.push_back(tempVal);
        sum += tempVal;
      }
    }
  }

  return sum;
}

// remove values in vector v which are greater than or equal to integer k
void greaterThanK(vector<int> &v, int k)
{
  // set temporary vector
  vector<int> temp;

  // iterate through v
  for(int i = 0; i < v.size(); i++)
  {
    // check k against current value, if k < value: push value into temporary vector
    if(k < v[i])
    {
      temp.push_back(v[i]);
    }
  }

  // set v = temporary vector, this only has values that were greater than or equal to k
  v = temp;
}

// find out whether array a is a subarray of array b, contiguity matters.
bool isSubarray(const vector<string> &a, const vector<string> &b)
{
  // edge cases
  // if a is empty it will be a subarray of any array b
  // if a is bigger than b it cannot be a subarray of b
  if(a.size() == 0) { return true; }
  if(a.size() > b.size()) { return false; }

  // loop through b
  for(int i = 0; i < b.size(); i++)
  {
    // check current element of b against first element of a. 
    // if that element matches:
    if(a[0] == b[i])
    {
      // set the current index of a and b to be 0 and i respectively
      int indexA = 0;
      int indexB = i;

      // while:
      // indexA is in bounds
      // indexB is in bounds
      // current a = current b:
      while(indexA < a.size() && indexB < b.size() && a[indexA] == b[indexB])
      {
        // increment indeces
        indexA++;
        indexB++;
      }
      
      // if above conditional allowed all elements of a to be counted for, or if
      // indexA = size of a, then a must be a subarray of b, return true
      if(indexA == a.size()) { return true; }
    }
  }

  // default return false
  return false;
}

// check primality of n
bool isPrimeA(int n)
{
  // if n < 2, return false as 1, 0 are not prime
  if(n < 2) { return false; }

  // initialize i at 2
  int i = 2;

  // while i < n
  while(i < n)
  {
    // if remainder of n / i = 0, n is not prime, as it is divisible by some i
    if(n % i == 0) { return false; }
    i++;
  }
  
  // default return true
  return true;
}

// calculates sum of all prime numbers less than n
int sumPrimesA(int n)
{
  // initialize sum
  int sum = 0;

  // start at n-1 since we do not include n
  n--;
  // from 1 < x < n, check if x is prime, if it is add to sum
  while(n > 1)
  {
    // check primality
    bool isPrime = isPrimeA(n);

    // if prime append to sum
    if(isPrime) { sum += n; }
    
    // decrement n
    n--;
  }

  return sum;
}

// same as isPrimeA but we check 2 <= i <= sqrt(n)
bool isPrimeB(int n)
{
  if(n < 2) { return false; }

  int i = 2;

  // check 2 to sqrt(n), if n / i has remained != 0, not prime
  while(i <= sqrt(n))
  {
    if(n % i == 0) { return false; }
    i++;
  }

  return true;
}

// same as sumPrimesA but we call isPrimeB instead
int sumPrimesB(int n)
{
  int sum = 0;

  n--;

  while(n > 0)
  {
    bool isPrime = isPrimeB(n);

    if(isPrime) { sum += n; }
    
    n--;
  }

  return sum;
}

// sum primes less than n
int sieveOfEratosthenes(int n)
{
  // if n < 2, invalid case, return 0
  if(n < 2) { return 0; }

  vector<int> v;

  int sum = 0;

  // push all a into vector such that 2 <= a <= sqrt(n)
  for(int a = 2; a <= n - 1; a++)
  {
    v.push_back(a);
  }

  // loop through v
  for(int k = 0; k < v.size(); k++)
  {
    // if v[k] is not prime, v[k] = 0
    // if number is not prime, then it must be a multiple of some i
    if(!(isPrimeB(v[k])))
    {
      v[k] = 0;
    }
  }

  // loop through appended vector v, add to sum any number in v > 0
  for(int j = 0; j < v.size(); j++)
  {
    if(v[j] > 0)
    {
      sum += v[j];
    }
  }
  
  return sum;
}

/*************************************************************
 * Your solutions ends here and do not change anything below *
 * ***********************************************************/

/***********************************************
 * Main and helper functions for quick testing *
 * *********************************************/
void readIntVector(vector<int> &v, int n);
void timePrimes();

int main(){
  int question = -1;
  cout << "Question: ";
  cin >> question;

  int n = 0, k = 0, m = 0;
  vector<int> v;
  string s = "";
  vector<string> a;
  vector<string> b;

  switch (question){
    case 1: //collatzLength
      cout << "Collatz Sequence n: ";
      cin >> n;
      cout << collatzLength(n) << endl;
      break;
    case 2: //printStats
      cout << "Print Stats Number of Values: ";
      cin >> n;
      cout << "Values: ";
      readIntVector(v, n);
      cout << "Stats: " << endl;
      printStats(v);
      break;
    case 3: //sumMultiples
      cout << "Sum Multiples Number of Values: ";
      cin >> n;
      cout << "Values: ";
      readIntVector(v, n);
      cout << "Max Value: ";
      cin >> k;
      cout << "Sum: ";
      cout << sumMultiples(v, k) << endl;
      break;
    case 4: //greaterThanK
      cout << "Greater than K Number of Values: ";
      cin >> n;
      cout << "Values: ";
      readIntVector(v, n);
      cout << "k: ";
      cin >> k;
      cout << "Result: ";
      greaterThanK(v, k);
      for (int j = 0; j < v.size(); j++){ cout << v[j] << " "; }
      break;
    case 5: //isSubarray
      cout << "Is Subarray Array Sizes: ";
      cin >> n >> m;
      cout << "Values for First Vector: ";
      for (int i = 0; i < n; i++){
        cin >> s;
        a.push_back(s);
      }
      cout << "Values for Second Vector: ";
      for (int i = 0; i < m; i++){
        cin >> s;
        b.push_back(s);
      }
      cout << "Result: ";
      cout << isSubarray(a, b) << endl;
      break;
    case 6: //naive prime sum
      cout << "Primes Max Value: ";
      cin >> n;
      cout << "Sum: " << sumPrimesA(n) << endl;
      break;
    case 7: //prime sum 2
      cout << "Primes Max Value: ";
      cin >> n;
      cout << "Sum: " << sumPrimesB(n) << endl;
      break;
    case 8: //sieve of eratosthenes
      cout << "Primes Max Value: ";
      cin >> n;
      cout << "Sum: " << sieveOfEratosthenes(n) << endl;
      break;
    case 9: //time primes
      cout << "Time Primes" << endl;
      timePrimes();
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

/***************************************************************************************************
 * Testing run times of different approaches to finding the sum of prime numbers under a threshold *
 * *************************************************************************************************/
void timePrimes(){
  int sum = -1;
  chrono::high_resolution_clock::time_point start;
  chrono::high_resolution_clock::time_point end;
  double elapsed = -1;
  vector<int> x = {10, 100, 1000, 10000, 100000, 500000};
  for (int i = 0; i < x.size(); i++)
  {
    cout << "Value: " << x[i] << endl;

    start = chrono::high_resolution_clock::now();
    sum = sumPrimesA(x[i]);
    end = chrono::high_resolution_clock::now();
    elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
    cout << "A ... Sum: " << sum << ", Time elapsed: " << elapsed << endl;

    start = chrono::high_resolution_clock::now();
    sum = sumPrimesB(x[i]);
    end = chrono::high_resolution_clock::now();
    elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
    cout << "B ... Sum: " << sum << ", Time elapsed: " << elapsed << endl;

    start = chrono::high_resolution_clock::now();
    sum = sieveOfEratosthenes(x[i]);
    end = chrono::high_resolution_clock::now();
    elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
    cout << "C ... Sum: " << sum << ", Time elapsed: " << elapsed << endl;
    cout << endl << endl;
  }

  cout << "Sieve of Eratosthenes on primes below 1 million" << endl;
  start = chrono::high_resolution_clock::now();
  long sum2 = sieveOfEratosthenes(1000000);
  end = chrono::high_resolution_clock::now();
  elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
  cout << "Sum: " << sum2 << ", Time elapsed: " << elapsed << endl;
  cout << endl << endl;
}

