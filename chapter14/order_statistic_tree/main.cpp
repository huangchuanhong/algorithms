#include <iostream>
#include "order_statistic_tree.h"
using namespace std;

int main()
{
  Tree t;
  Node *x; 
  for (int i=1; i<=9; ++i)
  {
    x = new Node(i);
    t.init_node(x);
    t.insert(x);
    t.print();
  }
  int r = t.key_rank(7);
  cout << "rank(7)="<<r<<endl;
  cout << "rank(7)="<<t.key_rank_recursive(7)<<endl;
  r = t.key_rank(11);
  cout << "rank(11)="<<r<<endl;
  cout << "rank(11)="<<t.key_rank_recursive(11)<<endl;
  x = t.search(10);
  cout << x->key << endl;
  x = t.search(11);
  if (x == t.nil)
    cout << "nil"<<endl;
  else
    cout << "not nil"<<endl;
  //x = t.search(6);
  //t.del(x);
  x = t.search(8);
  t.del(x);
  t.print();
  x = t.select(1);
  cout << x->key<<endl;
  x = t.select(5);
  cout << x->key <<endl; 
  cout << t.rank(x)<<endl;
  x = t.select(8);
  cout << t.rank(x)<<endl;
} 

