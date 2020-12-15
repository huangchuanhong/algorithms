#include <string>
#include <fstream>
using namespace std;

const int t = 2;

struct Node
{
  Node(const string &na);
  void disk_write();
  void disk_read();
  string name;
  int n;
  bool leaf;
  int key[2*t-1];
  int data[2*t-1];
  string c[2*t];
};

