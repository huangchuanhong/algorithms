#include <iostream>
#include <vector>
using namespace std;

void counting_sort(vector<int> &A, int k)
{
  vector<int> B(A.size());
  vector<int> C(k+1);
  for (int i=0; i<C.size(); ++i)
    C[i] = 0;
  for (int i=0; i<A.size(); ++i)
    C[A[i]] += 1;
  for (int i=1; i<C.size(); ++i)
    C[i] += C[i-1];
  for (int i=A.size()-1; i>=0; --i)
  {
    B[C[A[i]]-1] = A[i];
    --C[A[i]];
  }
  for (int i=0; i<A.size(); ++i)
    A[i] = B[i];
}

int main()
{
  vector<int> A{2, 5, 3, 0, 2, 3, 0, 3};
  for (int i=0; i<A.size(); ++i)
    cout << A[i]<<' ';
  cout << endl;
  counting_sort(A, 5);
  for (int i=0; i<A.size(); ++i)
    cout << A[i] << ' ';
  cout << endl;
}
