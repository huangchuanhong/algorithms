#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <queue>
#include "node.h"
using namespace std;

//struct Node
//{
//  void Node(const string &na);
//  void disk_write();
//  void disk_read();
//  string name;
//  int n;
//  bool leaf;
//  int key[2*t-1];
//  int data[2*t-1];
//  string c[2*t];
//};


class BTree
{
public:
  BTree(bool read_meta=true);
  void insert(int key, int data);
  void print();
  void disk_write_meta();
  void disk_read_meta();
private:
  void insert_nonefull(Node &node, int key, int data);
  Node split_child(Node &parent, Node &child, int i);
  string get_filename(int id);
  string root;
  size_t idx;
};

void BTree::disk_read_meta()
{
  ifstream f("meta.txt");
  f >> root >> idx;
}

void BTree::disk_write_meta()
{
  ofstream f("meta.txt");
  f << root << ' ' << idx;
}

void BTree::print()
{
  queue<string> q;
  q.push(root);
  while (!q.empty())
  {
    Node node(q.front());
    q.pop();
    node.disk_read();
    cout << "name="<<node.name<<endl;
    cout << "key="<<' ';
    for (int i=0; i<node.n; ++i)
      cout << node.key[i]<<' ';
    cout <<endl;
    cout << "data="<<' ';
    for (int i=0; i<node.n; ++i)
      cout << node.data[i]<<' ';
    cout << endl;
    if (node.leaf)
    {
      for (int i=0; i<=node.n; ++i)
      {
        cout << node.c[i]<<' ';
        q.push(node.c[i]);
      }
      cout << endl; 
    }
    cout <<endl;
  }
} 

BTree::BTree(bool read_meta)
{
  if (read_meta)
    disk_read_meta();
  else
  {
    root = "0.txt";
    Node node(root);
    node.disk_write();
    idx = 1;
  }
}

void BTree::insert_nonefull(Node &node, int key, int data)
{
  int i;
  for (i=0; i<node.n&&key>=node.key[i];++i);
  while (!node.leaf)
  {
    Node child(node.c[i]);
    child.disk_read();
    cout << "i="<<i<<endl;
    int j;
    for (int k=0; k<child.n; ++k)
      cout << child.key[k]<<' ';
    cout << endl;
    cout << "child.leaf="<<child.leaf<<endl;
    cout << "key="<<key<<endl;
    for (j=0; j<child.n&&key>=child.key[j];++j);
    cout << "j="<<j<<endl;
    if (child.n == 2*t-1)
    {
      Node rchild = split_child(node, child, i);
      cout << "rchild.name="<<rchild.name<<endl;
      if (j >= t)
      {
        node = rchild;
        i = j-t;
      }
      else
      {
        node = child; 
        i = j;
      }
    }
    else
    {
      node = child;
      cout << "node.leaf="<<node.leaf<<endl;
      i = j;
    }
  }
  for (int j=node.n-1; j>=i;--j)
  {
    node.key[j+1] = node.key[j];
    node.data[j+1] = node.data[j];
  }
  node.key[i] = key;
  node.data[i] = data;
  ++node.n;
  node.disk_write();
}

//BTree::BTree(const string &name)
//{
//  root = name;
//  idx = 1;
//}

string BTree::get_filename(int id)
{
  stringstream ss;
  ss << (idx++) << ".txt";
  string name;
  ss >> name;
  return name;
}

Node BTree::split_child(Node &parent, Node &child, int i)
{
  auto rname = get_filename(idx);
  // rchild
  Node rchild(rname);
  rchild.n = t-1;
  rchild.leaf = child.leaf;
  for (int j=0; j<t-1; ++j)
  {
    rchild.key[j] = child.key[t+j];
    rchild.data[j] = child.data[t+j];
    if (!rchild.leaf)
      rchild.c[j] = child.c[t+j];
  }
  if (!rchild.leaf)
    rchild.c[t-1] = child.c[2*t-1];
  // parent
  for (int j=parent.n-1; j>=i; --j)
  {
    parent.key[j+1] = parent.key[j];
    parent.data[j+1] = parent.data[j];
  } 
  parent.key[i] = child.key[t-1];
  parent.data[i] = child.data[t-1];
  for (int j=parent.n; j>=i+1; --j)
    parent.c[j+1] = parent.c[j];
  parent.c[i+1] = rname;
  ++parent.n;
  // child
  child.n = t-1;
  parent.disk_write();
  child.disk_write();
  rchild.disk_write();
  return rchild;
}

void BTree::insert(int key, int data)
{
  Node p(root);
  p.disk_read();
  if (p.n == 2*t-1)
  {
    auto name = get_filename(idx);
    Node node(name);
    node.n = 0;
    node.leaf = false;
    node.c[0] = root;
    root = node.name;
    split_child(node, p, 0);
    insert_nonefull(node, key, data);
  }
  else
    insert_nonefull(p, key, data);
}

int main()
{
  BTree t(false);
  t.insert(1, 1);
  t.insert(5, 5);
  t.insert(3, 3);
  t.insert(2, 2);
  //t.disk_write_meta();
  t.insert(9,9);
  t.insert(7,7);
  t.insert(100,100);
  cout << "insert 50"<<endl;
  t.insert(50, 50);
  t.insert(20, 20);
  cout << "insert 10"<<endl;
  t.insert(10, 10);
  t.insert(15, 15);
  t.insert(4,4);
  t.insert(5,5);
  t.insert(6,6);
  t.insert(8,8);
  t.insert(11, 11);
  t.insert(12, 12);
  t.insert(13, 13);
  t.insert(14, 14);
  t.disk_write_meta();
}
