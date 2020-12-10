// page 244, 16.2-2
#include <iostream>
#include <vector>
using namespace std;

void zero_one_knapsack_problem(const vector<int> &w, const vector<int> &v, int W, vector<vector<int>> &f)
{
  int n = w.size();
  for (int i=1; i<=W; ++i)
  {
    if (w[n-1] <= i)
      f[i][n-1] = v[n-1];
  }
  for (int i=1; i<=W; ++i)
  {
    for (int j=n-2; j>=0; --j)
    {
      if (w[j] > i)
        f[i][j] = f[i][j+1];
      else
      {
        int x = f[i-w[j]][j+1] + v[j];
        int y = f[i][j+1];
        if (x >= y)
          f[i][j] = x;
        else
          f[i][j] = y;
      }
    }
  }
}

void print(const vector<int> &w, const vector<int> &v, int W, const vector<vector<int>> &f)
{
  int i=W, j=0;
  int n = w.size();
  while (i > 0 && j <= n-1)
  {
    if (w[j] > i)
      ++j;
    else
    {
      int x = f[i-w[j]][j+1];
      int y = f[i][j+1];
      if (x >= y)
      {
        i -= w[j];
        if (i>0 && j<=n-1)
          cout << j << "->";
        else
          cout << j;
      }
      else
        ++j;
    }
  }
  cout << endl;
}

int main()
{
  vector<int> w{10, 20, 30};
  vector<int> v{60, 100, 120};
  int W = 50;
  vector<vector<int>> f(W+1, vector<int>(w.size(), 0));
  zero_one_knapsack_problem(w, v, W, f);
  //for (int i=0; i<f.size(); ++i)
  //{
  //  for (int j=0; j<f[0].size(); ++j)
  //    cout << f[i][j] << ' ';
  //  cout << endl;
  //}
  print(w, v, W, f); 
}
