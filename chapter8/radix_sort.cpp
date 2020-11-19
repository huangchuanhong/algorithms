#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

void counting_sort(vector<int> &A, int k)
{
  vector<int> B(A.size());
  vector<int> C(10);
  vector<int> Ak(A.size());
  for (int i=0; i<Ak.size(); ++i)
    Ak[i] = A[i]/int(pow(10,k))%10;
  for (int i=0; i<C.size(); ++i)
    C[i] = 0;
  for (int i=0; i<A.size(); ++i)
    C[Ak[i]] += 1;
  for (int i=1; i<C.size(); ++i)
    C[i] += C[i-1];
  for (int i=A.size()-1; i>=0; --i)
  {
    B[C[Ak[i]]-1] = A[i];
    --C[Ak[i]];
  }
  for (int i=0; i<A.size(); ++i)
    A[i] = B[i];
} 

void radix_sort(vector<int> &A, int d)
{
  for (int i = 0; i < d; ++i)
  {
     counting_sort(A, i);
  }
}

int main()
{
  vector<int> A{329, 457, 657, 839, 436, 720, 355};
  for (int i=0; i<A.size(); ++i)
    cout << A[i] << ' ';
  cout << endl;
  radix_sort(A, 3);
  for (int i=0; i<A.size(); ++i)
    cout << A[i] << ' ';
  cout << endl;
}
