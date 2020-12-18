#include <vector>
using namespace std;

namespace DisjointSet
{

struct Node;

struct HeadNode
{
  int weight;
  Node* head;
  Node* tail;
};

struct Node
{
  Node(int x):key(x),hp(NULL),next(NULL){}
  char key;
  HeadNode *hp;
  Node* next;
};

class DisjointSet
{
public:
  DisjointSet(){}
  ~DisjointSet();
  void make_set(Node *x);
  HeadNode* find_set(Node *x);
  void Union(Node *x, Node *y);
  void print();
private:
  vector<Node*> nps;
  vector<HeadNode*> hps;
};

}

