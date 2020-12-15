#include <iostream>
#include <sstream>
#include "node.h"
using namespace std;

//extern const int t = 2;

//struct Node
//{
//  void init_node(const string &na);
//  void disk_write();
//  void disk_read();
//  string name;
//  int n;
//  bool leaf;
//  int key[2*t-1];
//  int data[2*t-1];
//  string c[2*t];
//};

Node::Node(const string &na)
{
  name = na;
  n = 0;
  leaf = true;
}

void Node::disk_write()
{
  ofstream f(name);
  f << n <<' '<< leaf << ' '; 
  for (int i=0; i<n; ++i)
    f << key[i] <<' ';
  for (int i=0; i<n; ++i)
    f << data[i] << ' ';
  if (!leaf)
    for (int i=0; i<n+1; ++i)
      f << c[i]<<' ';
  f.close();
}

void Node::disk_read()
{
  ifstream f(name);
  f >> n >> leaf;
  for (int i=0; i<n; ++i)
    f >> key[i];
  for (int i=0; i<n; ++i)
    f >> data[i];
  if (!leaf)
    for (int i=0; i<n+1; ++i)
      f >> c[i];
  f.close();
}

//int main()
//{
//  //string name="test.txt";
//  //Node x(name);
//  //x.n = 3;
//  //for (int i=0; i<3; ++i)
//  //  x.key[i] = i;
//  //for (int i=0; i<3; ++i)
//  //  x.data[i] = 2*i;
//  //for (int i=0; i<4; ++i)
//  //{
//  //  stringstream ss;
//  //  ss << i << ".txt";
//  //  ss >> x.c[i];
//  //  cout << x.c[i]<<endl;
//  //}
//  //x.disk_write();
//  
//  string name = "test.txt";
//  Node x(name);
//  x.disk_read();
//  cout << "x.n="<<x.n<<endl;
//  cout << "x.leaf="<<x.leaf<<endl;
//  for (int i=0; i<3; ++i)
//    cout << x.key[i]<<' ';
//  cout <<endl;
//  for (int i=0; i<3; ++i)
//    cout << x.data[i]<<' ';
//  cout << endl;
//  for (int i=0; i<4; ++i)
//    cout << x.c[i]<<' '; 
//  cout << endl;
//}
