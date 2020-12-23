#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node;

struct HeadNode
{
  HeadNode(char k):key(k),parent(this),rank(0),next(NULL){}
  char key;
  HeadNode *parent;
  int rank;
  Node *next;
};

struct Node
{
  Node(int i, double w):id(i),weight(w),head(NULL),next(NULL){}
  int id;
  double weight;
  HeadNode *head;
  Node *next;
};

class Graph
{
public:
  Graph(const vector<char> &vs);
  void add_edge(int i, int j, double w, bool directed);
  void MST_kruscal(vector<pair<char, char>> &tree);
  void print_graph();
private:
  int find_set(int i);
  void Union(int i, int j);
  int n;
  HeadNode* *heads;
  vector<Node *> edges;
};

bool weight_less(Node* x, Node* y)
{
  if (x->weight <= y->weight)
    return true;
  else
    return false;
}

int Graph::find_set(int i)
{
  if (heads[i]->parent == heads[i])
    return i;
  else 
  {
    int j = find_set(heads[i]->parent->key-'a');
    heads[i]->parent = heads[j];
    return heads[j]->key-'a';
  } 
}

void Graph::Union(int i, int j)
{
  if (heads[i]->rank < heads[j]->rank) 
    swap(i, j);
  if (heads[i]->rank == heads[j]->rank)
  {
    ++heads[i]->rank;
    heads[j]->parent = heads[i];
  }
  else
    heads[j]->parent = heads[i];
}

void Graph::MST_kruscal(vector<pair<char, char>> &tree)
{
  sort(edges.begin(), edges.end(), weight_less);
  for (int i=0; i<edges.size(); ++i)
  {
    int i_set = find_set(edges[i]->id);
    int j_set = find_set(edges[i]->head->key - 'a');
    if (i_set != j_set)
    {
      Union(i_set, j_set);
      tree.push_back(make_pair(edges[i]->id+'a', edges[i]->head->key));
    }
  }
}

Graph::Graph(const vector<char> &vs)
{
  n = vs.size();
  heads = new HeadNode*[n];
  for (int i=0; i<n; ++i)
    heads[i] = new HeadNode(vs[i]);
}

void Graph::add_edge(int i, int j, double w, bool directed=false)
{
  Node *tmp = new Node(j, w);
  tmp->head = heads[i];
  tmp->next = heads[i]->next;
  heads[i]->next = tmp;
  edges.push_back(tmp);
  if (!directed)
  {
    tmp = new Node(i, w);
    tmp->head = heads[j];
    tmp->next = heads[j]->next;
    heads[j]->next = tmp;
  }
}

void Graph::print_graph()
{
  for (int i=0; i<n; ++i)
  {
    cout << i << "(parent="<<heads[i]->parent->key<<"): ";
    cout << heads[i]->key << "->";
    Node *p = heads[i]->next;
    while (p!=NULL)
    {
      cout << heads[p->id]->key << "(weight="<<p->weight <<", head="<<p->head->key<<") ->";
      p = p->next;
    }
    cout << endl;
  }
}

int id(char c)
{
  return c-'a';
}
int main()
{
  vector<char> vs{'a','b','c','d','e','f','g','h','i'};
  Graph graph(vs);
  graph.add_edge(id('a'), id('h'), 8);
  graph.add_edge(id('a'), id('b'), 4);
  graph.add_edge(id('b'), id('h'), 11);
  graph.add_edge(id('b'), id('c'), 8);
  graph.add_edge(id('c'), id('i'), 2);
  graph.add_edge(id('c'), id('f'), 4);
  graph.add_edge(id('c'), id('d'), 7);
  graph.add_edge(id('d'), id('f'), 14);
  graph.add_edge(id('d'), id('e'), 9);
  graph.add_edge(id('e'), id('f'), 10);
  graph.add_edge(id('f'), id('g'), 2);
  graph.add_edge(id('g'), id('i'), 6);
  graph.add_edge(id('g'), id('h'), 1);
  graph.add_edge(id('h'), id('i'), 7);
  graph.print_graph();
  vector<pair<char, char>> vec;
  graph.MST_kruscal(vec);
  for (int i=0; i<vec.size(); ++i)
    cout << "("<<vec[i].first << ',' << vec[i].second << ") ";
  cout << endl;
}
