#include "linked_list_disjoint_set.h"

namespace Graph
{
struct Node;

struct HeadNode
{
  HeadNode(char k):key(k),sn(new DisjointSet::Node(k)),next(NULL){}
  char key;
  DisjointSet::Node* sn;
  Node *next;
};

struct Node
{
  Node(int i):id(i),next(NULL){}
  int id;
  Node *next;
};

class Graph
{
public:
  Graph(int n_):n(n_),headnodes(new HeadNode*[n_]){}
  void create_demo();
  void print();
  int n;
  HeadNode* *headnodes;
};

}
