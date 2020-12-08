#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const double inf=1000000;

void optimial_binary_search_tree(vector<double>p, vector<double>d, vector<vector<double>>f, vector<vector<int>> &s)
{
  int n = d.size()-1;
  for (int i=0; i<=n; ++i)
    f[i][i] = d[i];
  for (int l=1; l<=n; ++l)
  {
    for (int i=0; i<=n-l; ++i)
    {
      int j = i+l;
      double pij = 0;
      double dij1=d[j];
      for (int k=i; k<j; ++k)
      {
        pij += p[k];
        dij1 += d[k];
      }
      double min_ij = inf;
      int root = -1;
      for (int k=i; k<j; ++k)
      {
        double x = f[i][k] + f[k+1][j] + pij + dij1;
        if (x < min_ij)
        {
          min_ij = x;
          root = k;
        }
      }
      f[i][j] = min_ij;
      s[i][j] = root;
    }
  }
}

void print(const vector<vector<int>> &s, int i, int j)
{
  if (i==j)
    return;
  if (i==j-1)
  {
    cout << i;
  }
  else
  {
    if (s[i][j] > i)
    {
      cout << '(';
      print(s, i, s[i][j]);
      cout <<')'<<s[i][j];
    }
    if (s[i][j]+1 < j)
    {
      cout <<'(';
      print(s, s[i][j]+1, j);
      cout << ')';
    }
  }
}

int print_discribe2(const vector<vector<int>> &s)
{
  queue<pair<int, int>> q;
  q.push({0, s.size()-1});
  cout << s[0][s.size()-1] << "is root"<<endl;
  while (!q.empty())
  {
    auto x = q.front();
    q.pop();
    int i = x.first;
    int j = x.second;
    if (s[i][j] > i)
    {
      int left = s[i][s[i][j]];
      cout << left << "is "<<s[i][j]<<"'s left"<<endl;
      q.push({i, s[i][j]});
    }
    if (j > s[i][j]+1)
    {
      int right = s[s[i][j]+1][j];
      cout << right << "is "<<s[i][j]<<"'s right"<<endl;
      q.push({s[i][j]+1, j});
    }
  }
}

int print_discribe_aux(const vector<vector<int>> &s, int i, int j)
{
  if (i == j)
    return -1;
  if (i+1 == j)
    return i;
  int left = print_discribe_aux(s, i, s[i][j]);
  if (left > 0)
    cout << left << "is" << s[i][j] << "'s left child"<<endl;
  int right = print_discribe_aux(s, s[i][j]+1, j);
  if (right > 0)
    cout << right << "is" << s[i][j] << "'s right child"<<endl;
  return s[i][j];
}
 
void print_discribe(const vector<vector<int>> &s)
{
  int i=0, j=s.size()-1;
  cout << s[i][j] << "is root"<<endl;
  print_discribe_aux(s, i, j); 
}

int main()
{
  vector<double> p{0.15, 0.1, 0.05, 0.1, 0.2};
  vector<double> d{0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
  vector<vector<double>> f(d.size(), vector<double>(d.size(), -1));
  vector<vector<int>> s(d.size(), vector<int>(d.size(), -1));
  optimial_binary_search_tree(p, d, f, s);
  print(s, 0, s.size()-1);
  cout << endl;
  print_discribe2(s);
}
