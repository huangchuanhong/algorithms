#include <iostream>
#include <vector>
using namespace std;

// page 226, 15.4-5
int longest_monotonically_increasing_subsequence(const vector<double> &A, vector<int> &pre, int &id)
{
  pre[0] = -1;
  vector<int> c(A.size(), 1);
  int max_c = 1;
  for (int i=0; i<A.size(); ++i)
  {
    int max_pre = -1;
    for (int j=i-1; j>=0; --j)
    {
      if (A[j] <= A[i] && c[j] > max_pre)
      {
        max_pre = c[j];
        pre[i] = j;
        c[i] = c[j] + 1;
        if (c[i] > max_c)
        {
          max_c = c[i];
          id = i;
        }
      }
    }
  }
  return max_c;
}

void print(const vector<double> &A, int id, const vector<int> &pre)
{
  if (pre[id] == -1)
    cout << A[id] << ' ';
  else
    print(A, pre[id], pre);
    cout << A[id] << ' ';
}

int main()
{
  vector<double> A{9,10,1,4,7,8,11,2,3,1,9,43,26,8,3,9,1,2,10,3,33,4,77,2345,5,1688,23,1,6,23,4,7,8,9,10};
  for (int i=0; i<A.size(); ++i)
    cout << A[i]<<' ';
  cout << endl;
  vector<int> pre(A.size(), -1);
  int id = -1;
  int max_c = longest_monotonically_increasing_subsequence(A, pre, id);
  cout << max_c<<endl;
  print(A, id, pre);
  cout << endl;
}
