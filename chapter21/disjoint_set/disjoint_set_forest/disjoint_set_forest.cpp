#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct Node
{
  Node(char c):key(c),rank(0),parent(this){}
  char key;
  Node *parent;
  int rank;
};

class DisjointSetForest
{
public:
  DisjointSetForest(){}
  void make_set(Node *x);
  Node* find_set(Node *x);
  void Union(Node *x, Node *y);
  void print();
private:
  vector<Node *> roots;
};

//void DisjointSetForest::print()
//{
//  bool *flags = new bool[roots.size()];
//  for (int i=0; i<roots.size(); ++i)
//    flags[i] = true;
//  for (int i=0; i<roots.size(); ++i)
//  {
//    if (flags[i] == false)
//      continue;
//    cout << roots[i]->key<<' ';
//    for (int j=i+1; j<roots.size(); ++j)
//    {
//      if (flags[j] == false)
//        continue;
//      if (find_set(roots[i]) == find_set(roots[j]))
//        cout << roots[j] << ' ';
//    }
//    cout << endl;
//  }
//}

void DisjointSetForest::print()
{
  for (int i=0; i<roots.size(); ++i)
  {
    cout << "key="<<roots[i]->key<<' ';
    cout << "parent="<<roots[i]->parent->key<<' ';
    cout << "rank="<<roots[i]->rank<<endl;
  }
}

void DisjointSetForest::make_set(Node *x)
{
  roots.push_back(x); 
}

Node* DisjointSetForest::find_set(Node *x)
{
  stack<Node *> ps;
  while (x->parent!=x)
  {
    ps.push(x);
    x = x->parent; 
  }
  while (!ps.empty())
  {
    auto *y = ps.top();
    ps.pop();
    y->parent = x;
  }
  return x;
}

void DisjointSetForest::Union(Node *x, Node *y)
{
  if (x->rank < y->rank)
    swap(x, y);
  if (x->rank == y->rank)
  {
    y->parent = x;
    ++x->rank;
  }
  else
    y->parent = x;
}

int main()
{
  DisjointSetForest set;
  Node *a = new Node('a');
  set.make_set(a);
  Node *b = new Node('b');
  set.make_set(b);
  Node *c = new Node('c');
  set.make_set(c);
  Node *d = new Node('d');
  set.make_set(d);
  Node *e = new Node('e');
  set.make_set(e);
  Node *f = new Node('f');
  set.make_set(f);
  Node *g = new Node('g');
  set.make_set(g); 
  Node *h = new Node('h');
  set.make_set(h);
  Node *i = new Node('i');
  set.make_set(i);
  Node *j = new Node('j');
  set.make_set(j);
  set.Union(b,d);
  set.Union(e,g);
  set.Union(a,c);
  set.Union(h,i);
  set.Union(a,b);
  set.Union(e,f);
  set.Union(b,c);
  set.print();
}
