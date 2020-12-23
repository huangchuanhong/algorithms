#include <iostream>
#include <vector>
using namespace std;

const int INF = 1000000;

struct Node;

struct HeadNode
{
  HeadNode(char c):key(c),weight(INF),heap_id(INF),connect(NULL),next(NULL){}
  char key;
  int heap_id; // id in minheap, changes when adapt the minheap
  double weight; // the minimum weight connected to the generating mst
  HeadNode *connect; // which headnode in the generating mst to connect
  Node *next; // next Node
};

struct Node
{
  Node(int i, double w):id(i),weight(w),next(NULL){}
  int id;
  double weight; 
  Node *next;
};

struct Graph
{
  Graph(const vector<char> &keys);
  void add_edge(int i, int j, double w);
  int n;
  HeadNode* *heads;
};

class MinHeap
{
public:
  MinHeap(const vector<HeadNode*> v);
  void min_heapify(int i);
  HeadNode* extract_min();
  void decrease_key(HeadNode* x, double w);
  void print();
  int size; 
private:
  int parent(int i){return (i+1)/2-1;}
  int left_child(int i){return 2*i+1;}
  int right_child(int i){return 2*i+2;}
  vector<HeadNode*> vec;
};

void MinHeap::print()
{
  for (int i=0; i<size; ++i)
    cout << "key="<<vec[i]->key<<" heap_id="<<vec[i]->heap_id<<" weight="<<vec[i]->weight<<" parent="<<vec[i]->connect<<endl; 
}

Graph::Graph(const vector<char> &keys)
{
  n = keys.size();
  heads = new HeadNode*[n];
  for (int i=0; i<n; ++i)
  {
    heads[i] = new HeadNode(keys[i]);
  }
}

void Graph::add_edge(int i, int j, double w)
{
  Node *tmp = new Node(j, w);
  tmp->next = heads[i]->next;
  heads[i]->next = tmp;
  tmp = new Node(i, w);
  tmp->next = heads[j]->next;
  heads[j]->next = tmp;
}

HeadNode* MinHeap::extract_min()
{
  HeadNode *min = vec[0];
  min->heap_id = -1;
  vec[0] = vec[size-1];
  vec[0]->heap_id = 0;
  --size;
  min_heapify(0);
  return min;
}

void MinHeap::decrease_key(HeadNode *x, double w)
{
  if (w >= x->weight)
    return;
  x->weight = w;
  int i = x->heap_id;
  int p = parent(i);
  while (p>=0)
  {
    if (vec[p]->weight > vec[i]->weight)
    {
      swap(vec[i], vec[p]);
      swap(vec[i]->heap_id, vec[p]->heap_id);
      i = p;
      p = parent(i);
    }
    else break;
  }
}

MinHeap::MinHeap(const vector<HeadNode*> v)
{
  vec = v;
  size = vec.size();
  for (int i=parent(size-1); i>=0; --i)
    min_heapify(i);
}

void MinHeap::min_heapify(int i)
{
  int c = left_child(i);
  while (c<=size)
  {
    int rc = right_child(i);
    if (rc<=size && vec[c]->weight > vec[rc]->weight)
      c = rc;
    if (vec[i]->weight <= vec[c]->weight)
      break;
    swap(vec[i], vec[c]);
    swap(vec[i]->heap_id, vec[c]->heap_id);
    i = c;
    c = left_child(i);
  }
}

vector<HeadNode*> MST_prim(Graph &graph)
{
  vector<HeadNode*> mst;
  vector<HeadNode*> v;
  graph.heads[0]->weight = 0;
  for (int i=0; i<graph.n; ++i)
  {
    graph.heads[i]->heap_id = i;
    v.push_back(graph.heads[i]);
  }
  MinHeap Q(v);
  while (Q.size != 0)
  {
    HeadNode *min = Q.extract_min();
    if (min->connect != NULL)
      mst.push_back(min);
    Node *q = min->next;
    while (q != NULL)
    {
      if (graph.heads[q->id]->heap_id >= 0)
      {
        graph.heads[q->id]->connect = min;
        Q.decrease_key(graph.heads[q->id], q->weight);
      }
      q = q->next;
    }
  } 
  return mst;
}

int id(char x)
{
  return x - 'a';
}

int main()
{
  vector<char> keys{'a','b','c','d','e','f','g','h','i'};
  Graph graph(keys);
  graph.add_edge(id('a'),id('b'),4);
  graph.add_edge(id('a'),id('h'),8);
  graph.add_edge(id('b'),id('c'),8);
  graph.add_edge(id('b'),id('h'),11);
  graph.add_edge(id('c'),id('d'),7);
  graph.add_edge(id('c'),id('f'),4);
  graph.add_edge(id('c'),id('i'),2);
  graph.add_edge(id('d'),id('e'),9);
  graph.add_edge(id('d'),id('f'),14);
  graph.add_edge(id('e'),id('f'),10);
  graph.add_edge(id('f'),id('g'),2);
  graph.add_edge(id('g'),id('h'),1);
  graph.add_edge(id('g'),id('i'),6);
  graph.add_edge(id('h'),id('i'),7);
  vector<HeadNode*> tree = MST_prim(graph); 
  for (int i=0; i<tree.size(); ++i)
    cout << "("<<tree[i]->connect->key << "," << tree[i]->key << ") ";
  cout << endl;
}
