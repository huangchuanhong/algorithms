#include <iostream>
#include <string>
#include <vector>
using namespace std;

int lcs(const string &s1, const string &s2, vector<vector<char>> &s, vector<vector<int>> &m)
{
  size_t h = s1.size() + 1;
  size_t w = s2.size() + 1;
  for (int i=0; i<w; ++i)
    m[0][i] = 0;
  for (int j=0; j<h; ++j)
    m[j][0] = 0;
  for (int i=1; i<h; ++i)
  {
    for (int j=1; j<w; ++j)
    {
      if (s1[i-1] == s2[j-1])
      {
        m[i][j] = m[i-1][j-1] + 1;
        s[i][j] = '0';
      }
      else if (m[i-1][j] >= m[i][j-1])
      {
        m[i][j] = m[i-1][j];
        s[i][j] = '^';
      }
      else
      {
        m[i][j] = m[i][j-1];
        s[i][j] = '<';
      }
    }
  }
  return m[h-1][w-1];
}

void print(const string &s1, const vector<vector<char>> &s, int i, int j)
{
  if (i==0 || j==0)
    return;
  else if (s[i][j] == '<')
    print(s1, s, i, j-1);
  else if (s[i][j] == '^')
    print(s1, s, i-1, j);
  else
  {
    print(s1, s, i-1, j-1);
    cout << s1[i-1];
  }
}

// page 226, 15.4-2
void print_wo_s(const string &s1, const string &s2, const vector<vector<int>> &m, int i, int j)
{
  if (i==0 || j==0)
    return;
  if (s1[i-1] == s2[j-1])
  {
    print_wo_s(s1, s2, m, i-1, j-1);
    cout << s1[i-1];
  }
  else if (m[i][j-1] >= m[i-1][j])
    print_wo_s(s1, s2, m, i, j-1);
  else
    print_wo_s(s1, s2, m, i-1, j);
}

// page 226, 15-4.3
void memorized_lcs(const string &s1, const string &s2, vector<vector<int>> &m, int i, int j)
{
  if (i==0 || j==0)
    m[i][j] = 0;
  else if (m[i][j] >= 0)
    return;
  else
  {
    if (s1[i-1] == s2[j-1])
    {
      memorized_lcs(s1, s2, m, i-1, j-1);
      m[i][j] = m[i-1][j-1] + 1;
    }
    else
    {
      memorized_lcs(s1, s2, m, i-1, j);
      memorized_lcs(s1, s2, m, i, j-1);
      if (m[i-1][j] >= m[i][j-1])
        m[i][j] = m[i-1][j];
      else
        m[i][j] = m[i][j-1];
    }
  }
}

void memorized_lcs_main()
{
  string s1="ABCBDAB";
  string s2="BDCABA";
  cout << "s1="<<s1<<endl;;
  cout << "s2="<<s2<<endl;;
  vector<vector<int>> m(s1.size()+1, vector<int>(s2.size()+1, -1));
  memorized_lcs(s1, s2, m, s1.size(), s2.size());
  for (int i=0; i<m.size(); ++i)
  {
    for (int j=0; j<m[0].size(); ++j)
      cout << m[i][j]<<' ';
    cout << endl;
  }
  cout << m[s1.size()][s2.size()]<<endl;
}

int main()
{
  string s = "memorized_lcs_main";
  if (s == "memorized_lcs_main")
    memorized_lcs_main();
  else if (s== "lcs")
  {
    string s1="ABCBDAB";
    string s2="BDCABA";
    cout << "s1="<<s1<<endl;;
    cout << "s2="<<s2<<endl;;
    vector<vector<char>> s(s1.size()+1, vector<char>(s2.size()+1, '-'));
    vector<vector<int>> m(s1.size()+1, vector<int>(s2.size()+1, -1));
    int c = lcs(s1, s2, s, m);
    cout << c<<endl; 
    for (int i=0; i<s.size(); ++i)
    {
      for (int j=0; j<s[0].size(); ++j)
        cout << s[i][j]<<' ';
      cout << endl;
    }  
    cout << endl;
    for (int i=0; i<m.size(); ++i)
    {
      for (int j=0; j<m[0].size(); ++j)
        cout << m[i][j]<<' ';
      cout << endl;
    }
    print(s1, s, s.size()-1, s[0].size()-1);
    cout << endl;
    print_wo_s(s1, s2, m, s.size()-1, s[0].size()-1);
    cout << endl;
  }
}
