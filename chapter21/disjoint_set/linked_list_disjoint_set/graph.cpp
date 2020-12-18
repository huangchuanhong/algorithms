#include <iostream>
#include "graph.h"
using namespace std;

namespace Graph
{

void Graph::create_demo()
{
  n = 10;
  headnodes = new HeadNode*[n];
  for (int i=0; i<n; ++i)
    headnodes[i] = new HeadNode('a'+i);
  headnodes[0]->next = new Node(1);
  headnodes[0]->next->next = new Node(2);
  headnodes[1]->next = new Node(0);
  headnodes[1]->next->next = new Node(2);
  headnodes[1]->next->next->next = new Node(3);
  headnodes[2]->next = new Node(0);
  headnodes[2]->next->next = new Node(1);
  headnodes[3]->next = new Node(1);
  headnodes[4]->next = new Node(5);
  headnodes[4]->next->next = new Node(6);
  headnodes[5]->next = new Node(4);
  headnodes[6]->next = new Node(4);
  headnodes[7]->next = new Node(8);
  headnodes[8]->next = new Node(7);
}

void Graph::print()
{
  for (int i=0; i<n; ++i)
  {
    cout << headnodes[i]->key << ' ';
    auto *p = headnodes[i]->next;
    while (p!=NULL)
    {
      cout << headnodes[p->id]->key<<' ';
      p = p->next;
    }
    cout << endl;
  }
}

}

//int main()
//{
//  Graph::Graph graph(10);
//  graph.create_demo();
//  graph.print();
//}
