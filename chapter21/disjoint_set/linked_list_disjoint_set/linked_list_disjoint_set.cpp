#include <iostream>
#include "linked_list_disjoint_set.h"
using namespace std;

namespace DisjointSet
{

void DisjointSet::print()
{
  for (int i=0; i<hps.size(); ++i)
  {
    if (hps[i]->weight != 0)
    {
      auto *p = hps[i]->head;
      while (p!=NULL)
      {
        cout << p->key<<' ';
        p = p->next;
      }
      cout << endl;
    }
  } 
}

DisjointSet::~DisjointSet()
{
  for (int i=0; i<hps.size(); ++i)
    delete hps[i];
}

void DisjointSet::make_set(Node *x)
{
  nps.push_back(x);
  HeadNode *headnode = new HeadNode();
  headnode->weight = 1;
  headnode->head = headnode->tail = x;
  x->hp = headnode;
  hps.push_back(headnode);
}

HeadNode* DisjointSet::find_set(Node *x)
{
  return x->hp;
}

void DisjointSet::Union(Node *x, Node *y)
{
  HeadNode *hx = find_set(x);
  HeadNode *hy = find_set(y);
  if (hx != hy)
  {
    if (hx->weight < hy->weight)
      swap(hx, hy);
    hx->tail->next = hy->head;
    Node *p = hy->head;
    while (p != NULL)
    {
      p->hp = hx;
      p = p->next;
    }
    hx->tail = hy->tail;
    hx->weight += hy->weight;
    hy->head = hy->tail = NULL;
    hy->weight = 0;
  }
}

}

//int main()
//{
//  //using namespace DisjointSet;
//  DisjointSet::DisjointSet set;
//  DisjointSet::Node *a = new DisjointSet::Node('a');
//  set.make_set(a);
//  DisjointSet::Node *b = new DisjointSet::Node('b');
//  set.make_set(b);
//  DisjointSet::Node *c = new DisjointSet::Node('c');
//  set.make_set(c);
//  DisjointSet::Node *d = new DisjointSet::Node('d');
//  set.make_set(d);
//  DisjointSet::Node *e = new DisjointSet::Node('e');
//  set.make_set(e);
//  DisjointSet::Node *f = new DisjointSet::Node('f');
//  set.make_set(f);
//  DisjointSet::Node *g = new DisjointSet::Node('g');
//  set.make_set(g);
//  DisjointSet::Node *h = new DisjointSet::Node('h');
//  set.make_set(h);
//  DisjointSet::Node *i = new DisjointSet::Node('i');
//  set.make_set(i);
//  DisjointSet::Node *j = new DisjointSet::Node('j');
//  set.make_set(j);
//  set.Union(b,d);
//  set.Union(e,g);
//  set.Union(a,c);
//  set.Union(h,i);
//  set.Union(a,b);
//  set.Union(e,f);
//  set.Union(b,c);
//  set.print();   
//}
