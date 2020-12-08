#include <iostream>
#include <vector>
#include <string>
using namespace std;

double memorized_cut_rob_aux(int n, const vector<double> &p, vector<int> &s, vector<double> &r)
{
  if (r[n] != -10000000)
    return r[n];
  if (n == 0)
    return 0;
  for (int i=1; i<=n; ++i)
  {
    double q = memorized_cut_rob_aux(n-i, p, s, r) + p[i];
    if (q > r[n])
    {
      r[n] = q;
      s[n] = i;
    }
  }
  return r[n];
}

double memorized_cut_rob(int n, const vector<double> &p, vector<int> &s)
{
  vector<double> r(p.size(), -10000000);
  r[0] = 0;
  memorized_cut_rob_aux(n, p, s, r);
}

double bottom_up_cut_rob(int n, const vector<double> &p, vector<int> &s)
{
  vector<double> r(p.size(), -1);
  r[0] = 0;
  for (int m=1; m<=n; ++m)
    for (int i=1; i<=m; ++i)
    {
      if (p[i] + r[m-i] > r[m])
      {
        r[m] = p[i] + r[m-i];
        s[m] = i;
      }
    }
  return r[n];
}

//page 210, 15.1.3
double cut_rob_with_cut_cost(int n, double c, const vector<double> &p, vector<int>&s)
{
  vector<int> r(p.size(), -1000000);
  r[0] = 0;
  for (int m=1; m<=n; ++m)
  {
    for (int i=1; i<m; ++i)
    {
      if (p[i] + r[m-i] - c > r[m])
      {
        r[m] = p[i] + r[m-i] - c;
        s[m] = i;
      }
    }
    if (p[m] > r[m])
    {
      r[m] = p[m];
      s[m] = m;
    }
  }
  return r[n];
}

int main()
{
  string s = "memorized_cut_rob"; 
  if (s=="bottom_up_cut_rob")
  {
    int n=9;
    vector<double> p{0,1,5,8,9,10,17,17,20,24,30};
    vector<int> s(11, -1);
    double q = bottom_up_cut_rob(n, p, s);
    cout << "q="<<q<<endl;
    while (n > 0)
    {
      cout << s[n]<<' ';
      n = n - s[n];
    }
    cout << endl;
  }
  else if (s == "cut_rob_with_cut_cost")
  {
    int n=4;
    vector<double> p{0,1,5,8,9,10,17,17,20,24,30};
    vector<int> s(11, -1);
    double c = 2;
    double q = cut_rob_with_cut_cost(n, c, p, s);
    cout << "q="<<q<<endl;
    while (n > 0)
    {
      cout << s[n]<<' ';
      n = n - s[n];
    }
    cout << endl;
  }
  else if (s == "memorized_cut_rob")
  {
    int n=10;
    vector<double> p{0,1,5,8,9,10,17,17,20,24,30};
    vector<int> s(11, -1);
    double q = memorized_cut_rob(n, p, s);
    cout << "q="<<q<<endl;
    while (n > 0)
    {
      cout << s[n]<<' ';
      n = n - s[n];
    }
    cout << endl;
  }
}
