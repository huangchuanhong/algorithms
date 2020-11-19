#include <iostream>
#include <vector>
using namespace std;

void insert_sort(vector<double> &A)
{
  for (int i=1; i<A.size(); ++i)
  {
    double curr = A[i];
    int j;
    for (j=i-1; j>=0; --j)
    {
      if (curr < A[j])
        A[j+1] = A[j];
      else
        break;
    }
    A[j+1] = curr;
  }
}

void bucket_sort(vector<double> &A)
{
  int n = A.size();
  vector<vector<double>> bucket(n);
  for (int i=0; i<n; ++i)
  {
    bucket[int(A[i]*n)].push_back(A[i]);
  }
  for (int i=0; i<n; ++i)
  {
    if (bucket[i].empty())
      continue;
    insert_sort(bucket[i]);
  }
  int j=0;
  for (int i=0; i<n; ++i)
  {
    if (bucket[i].empty())
      continue;
    for (int k=0; k<bucket[i].size(); ++k)
    {
      A[j++] = bucket[i][k];
    }
  }
}

int main()
{
  vector<double> A{0.79, 0.13, 0.16, 0.64, 0.39, 0.20, 0.89, 0.53, 0.71, 0.42};
  for (int i=0; i<A.size(); ++i)
    cout << A[i]<<' ';
  cout << endl;
  bucket_sort(A);
  for (int i=0; i<A.size(); ++i)
    cout << A[i]<<' ';
  cout << endl;
}

