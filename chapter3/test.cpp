#include <iostream>
#include <random>
#include <float.h>
using namespace std;

int main()
{
  static default_random_engine e;
  static uniform_real_distribution<double> u(-100, 100);
  vector<double> a(10);
  for (int i=0; i<a.size(); ++i)
  {
    a[i] = u(e);
  }
  for (int i=0; i<a.size(); ++i)
    cout << a[i]<<' ';
  cout << endl;
}
