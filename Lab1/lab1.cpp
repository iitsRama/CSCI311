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

//Amar Bulic
//013040249

//given any integer n, if n is even: n/2, if n id odd: 3n+1, until n = 1, return # of steps
int collatzLength(int n){

  //make sure n is not 0
  if(n == 0) { return 0; }

  int count = 0;

  while(abs(n) != 1)
  {
    if(n % 2 == 0)
    {
      n /= 2;
      count++;
    }
    else
    {
      n = (3 * n) + 1;
      count++;
    }
  }

  return count;
}

void printStats(const vector<int> &v)
{
  if(v.size() == 0) 
  {
    std::cout << "Empty vector" << std::endl;
    return;
  }

  int minimum = v.front();
  int maximum = v.front();
  float sum = v.front();
  
  for(int i = 1; i < v.size(); i++)
  {
    sum += v[i];

    if(v[i] > maximum)
    {
      maximum = v[i];
    }
    if(v[i] < minimum)
    {
      minimum = v[i];
    }
  }

  float mean = sum / (v.size());

  std::cout << minimum << " " << mean << " " << maximum << std::endl;
}

int sumMultiples(const vector<int> &v, int n)
{
  if(v.empty() || n <= 0) { return 0; }

  int sum = 0;
  vector<int> multiples;

  for(int i = 0; i < v.size(); i++)
  {
    int value = v[i];
    for(int tempVal = value; tempVal < n; tempVal += value)
    {
      bool duplicate = false;

      for(int j = 0; j < multiples.size(); j++)
      {
        if(multiples[j] == tempVal)
        {
          duplicate = true;
          break;
        }
      }

      if(!duplicate)
      {
        multiples.push_back(tempVal);
        sum += tempVal;
      }
    }
  }

  return sum;
}

void greaterThanK(vector<int> &v, int k)
{
  vector<int> temp;

  for(int i = 0; i < v.size(); i++)
  {
    if(k < v[i])
    {
      temp.push_back(v[i]);
    }
  }

  v = temp;
}

bool isSubarray(const vector<string> &a, const vector<string> &b)
{
  //edge cases 
  if(a.size() == 0) { return true; }
  if(a.size() > b.size()) { return false; }

  for(int i = 0; i < b.size(); i++)
  {
    if(a[0] == b[i])
    {
      int indexA = 0;
      int indexB = i;

      while(indexA < a.size() && indexB < b.size() && a[indexA] == b[indexB])
      {
        indexA++;
        indexB++;
      }
      
      if(indexA == a.size()) { return true; }
    }
  }

  return false;
}

bool isPrimeA(int n)
{
  if(n < 2) { return false; }

  int i = 2;

  while(i < n)
  {
    if(n % i == 0) { return false; }
    i++;
  }
  
  return true;
}

int sumPrimesA(int n)
{
  int sum = 0;

  while(n > 0)
  {
    bool isPrime = isPrimeA(n);

    if(isPrime) { sum += n; }
    
    n--;
  }

  return sum;
}

bool isPrimeB(int n)
{
  if(n < 2) { return false; }

  int i = 2;

  while(i <= sqrt(n))
  {
    if(n % i == 0) { return false; }
    i++;
  }

  return true;
}

int sumPrimesB(int n)
{
  int sum = 0;

  while(n > 0)
  {
    bool isPrime = isPrimeB(n);

    if(isPrime) { sum += n; }
    
    n--;
  }

  return sum;
}

int sieveOfEratosthenes(int n)
{

  vector<int> v;

  int a = 2;

  int sum = 0;

  while(a <= n - 1)
  {
    v.push_back(a);
    a++;
  }

  int i = 2;
  while(i <= sqrt(n))
  {
    int index = i;

    while(index < v.size())
    {
      if(v[index] % i == 0)
      {
        v[index] = 0;
      }
      index++;
    }

    i++;
  }

  int j = 0;

  while(j < v.size())
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

