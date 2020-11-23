#include <iostream>
#include <vector>
using namespace std;

// select int within [p, r]
int random_select(int p, int r)
{
  int x = rand()%(r-p+1) + p;
  return x;
}

int randomized_partition(vector<double> &A, int p, int r)
{
  int q = random_select(p, r);  
  swap(A[q], A[r]);
  int i = p - 1;
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

double randomized_select_recursive(vector<double> &A, int p, int r, int i)
{
  if (p == r)
    return A[p];
  int q = randomized_partition(A, p, r);
  int k = q - p + 1;
  if (k == i)
    return A[k];
  if (k > i)
    return randomized_select_recursive(A, p, q-1, i);
  if (k < i)
    return randomized_select_recursive(A, q+1, r, i-k);
}

double randomized_select_loop(vector<double> &A, int p, int r, int i)
{
  if (p==r)
    return A[p];
  while (true)
  {
    int q = randomized_partition(A, p, r);
    int k = q - p + 1;
    if (k == i)
      return A[q];
    if (k > i)
    {
      r = q-1;
    }
    if (k < i)
    {
      p = q+1;
      i = i - k;
    }
  }
}

int main()
{
  vector<double> A{3,2,9,0,7,5,4,8,6,1};
  for (int i=0; i<A.size(); ++i)
    cout << A[i] << ' ';
  cout << endl;
  cout << "select i="<<8<<endl;
  int num = randomized_select_loop(A, 0, A.size()-1, 8);
  cout << "selected num="<<num<<endl;
}
