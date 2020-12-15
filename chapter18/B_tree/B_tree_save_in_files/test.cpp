#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

int main()
{
  int key = 2;
  int i;
  for (i=0; i<4&&key>=i; ++i);
  cout <<i<<endl;
}
