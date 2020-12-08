#include <iostream>
#include <vector>
using namespace std;

const int n=3;
const int inf = 100000000;

int matrix_chain_order(int *p, int m[n][n], int s[n][n])
{
  for (int i=0; i<n; ++i)
    m[i][i] = 0;
  for (int l=2; l<=n; ++l)
  {
    for (int i=0; i<=n-l; ++i)
    {
      int j = i+l-1;
      m[i][j] = inf;
      for (int k = i; k<j; ++k)
      {
        int q = m[i][k] + m[k+1][j] + p[i]*p[k+1]*p[j+1];
        if (q < m[i][j])
        {
          m[i][j] = q;
          s[i][j] = k;
        }
      }
    }
  }
  return m[0][n-1];
}

void print(int s[n][n], int i, int j)
{
  if (i==j)
    cout << "a"<<i;
  else
  {
    cout << "(";
    print(s, i, s[i][j]);
    print(s, s[i][j]+1, j);
    cout << ")";
  }
}

void print(int s[n][n])
{
  print(s, 0, n-1);
  cout << endl;
}

vector<vector<double>> matrix_multiply(vector<vector<double>> a, vector<vector<double>> b)
{
  int ar = a.size();
  int ac = a[0].size();
  int bc = b[0].size();
  vector<vector<double>> c;
  for (int i=0; i<ar; ++i)
  {
    vector<double> vec;
    for (int j=0; j<bc; ++j)
    {
      double x = 0;
      for (int k=0; k<ac; ++k)
        x += a[i][k] * b[k][j];
      vec.push_back(x);
    }
    c.push_back(vec);
  }
  return c;
}

// page 215, 15-2-2
vector<vector<double>> matrix_chain_multiply(const vector<vector<vector<double>>> &A, int s[n][n], int i, int j)
{
  if (i == j)
    return A[i];
  if (i+1 == j)
  {
    auto a = A[i];
    auto b = A[j];
    auto c = matrix_multiply(a,b);
    return c;
  } 
  else
  {
    auto c1 = matrix_chain_multiply(A, s, i, s[i][j]);
    auto c2 = matrix_chain_multiply(A, s, s[i][j]+1, j);
    auto c = matrix_multiply(c1, c2);
    return c;
  }
}

void matrix_chain_multiply_main()
{
  int p[] = {3,1,3,2};
  int m[n][n];
  int s[n][n];
  int x = matrix_chain_order(p, m, s);
  cout << x<< endl;
  print(s);
  vector<vector<double>> a1{{1},{2},{3}};
  vector<vector<double>> a2{{4,5,6}};
  vector<vector<double>> a3{{7,8},{9,10},{11,12}};
  vector<vector<vector<double>>> A{a1,a2,a3};
  auto c = matrix_chain_multiply(A, s, 0, 2); 
  for (int i=0; i<c.size(); ++i)
  {
    for (int j=0; j<c[0].size(); ++j)
      cout << c[i][j]<<' ';
    cout << endl;
  }
}


int main()
{
  //int p[] = {30, 35, 15, 5, 10, 20, 25};
  //int m[n][n];
  //int s[n][n];
  //int x = matrix_chain_order(p, m, s);
  //cout << x<<endl;
  //print(s);
  matrix_chain_multiply_main(); 
}

