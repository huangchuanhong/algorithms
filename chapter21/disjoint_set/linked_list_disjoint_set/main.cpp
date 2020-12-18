#include <iostream>
#include "graph.h"
using namespace std;

int main()
{
  Graph::Graph graph(10);
  graph.create_demo();
  DisjointSet::DisjointSet set;
  for (int i=0; i<10; ++i)
    set.make_set(graph.headnodes[i]->sn);
  for (int i=0; i<10; ++i)
  {
    auto *x = graph.headnodes[i]->sn;
    auto *p = graph.headnodes[i]->next;
    while (p!=NULL)
    {
      auto *y = graph.headnodes[p->id]->sn;
      set.Union(x,y);
      p = p->next;
    }
  }  
  set.print();
}
