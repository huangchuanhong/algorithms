#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

void insert_sort(vector<double> &A, int p, int r, int stride)
{
  for (int i=p+stride; i<=r; i+=stride)
  {
    double curr = A[i];
    int j;
    for (j=i-stride; j>=p; j-=stride)
    {
      if (A[j] > curr)
      {
        A[j+stride] = A[j];
      }
      else
        break;
    }
    A[j+stride] = curr;
  }
}

int partition(vector<double> &A, int p, int r)
{
  int i = p - 1;
  for (int j=p; j<r; ++j)
  {
    if (A[j] <= A[r])
    {
      i += 1;
      swap(A[i], A[j]);
    }
  }
  swap(A[i+1], A[r]);
  return i+1;
}

int select(vector<double> &A, int p, int r, int ith, int stride)
{
  int num_medians = (r - p + 1) / (stride * 5);
  if (num_medians == 0)
  {
    insert_sort(A, p, r, stride);
    return p + (ith-1)*stride;
  }
  for (int i=p; i<=r; i+=5*stride)
  {
    insert_sort(A, i, min(r, i + 5*stride - 1), stride);
  }
  int m = select(A, p+stride*2, r, (num_medians+1) / 2, stride*5);
  swap(A[m], A[r]);
  int q = partition(A, p, r);
  int k = q - p + 1;
  if (k == ith)
    return q;
  if (k > ith)
    return select(A, p, q-1, ith, stride);
  if (k < ith)
    return select(A, q+1, r, ith-k, stride);
}

int main()
{
  int ith = 14;
  vector<double> A{23, 5, 6, 24, 1, 13, 3, 19, 18, 7, 2, 20, 11, 8, 12, 9, 4, 17, 15, 10, 26, 14, 16, 21, 22, 25, 26, 28, 27};
  for (int i=0; i<A.size(); ++i)
    cout << A[i]<<' ';
  cout << endl;
  vector<double> B(A);
  sort(B.begin(), B.end());
  for (int i=0; i<B.size(); ++i)
    cout << B[i] << ' ';
  cout << endl;
  int k = select(A, 0, A.size() - 1, ith, 1);
   sort(B.begin(), B.end());
  cout << "select "<<ith<<"'s="<<A[k] << endl;
}
