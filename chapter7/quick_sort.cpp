#include <iostream>
#include <vector>
using namespace std;

int partition(vector<double> &A, int p, int r)
{
  int i = p-1;
  for (int j=p; j<r; ++j)
  {
    if (A[j] <= A[r])
    {
      i += 1;
      swap(A[j], A[i]);
    }
  }
  swap(A[i+1], A[r]);
  return i+1;
}

void quick_sort(vector<double> &A, int p, int r)
{
  if (p >= r) 
    return;
  int q = partition(A, p, r);
  quick_sort(A, p, q-1);
  quick_sort(A, q+1, r);
}

int main()
{
  vector<double> A={0, 5, 3, 17, 10, 84, 19, 6, 22, 9};
  for (int i=0; i<A.size(); ++i)
    cout << A[i]<<' ';
  cout << endl;
  quick_sort(A, 0, A.size() - 1);
  for (int i=0; i<A.size(); ++ i)
    cout << A[i]<< ' ';
  cout << endl;
}
