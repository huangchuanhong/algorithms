#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1000000000;

struct Node
{
  Node(int k):id(k),next(NULL){}
  int id;
  Node *next;
};

class Graph
{
public:
  Graph(int n);
  void add_edge(int i, int j, bool directed);
  void BFS(int i); 
  void DFS();
  void SCC(Node *head);
  void SCC_visit(Node *x);
  Node* topological_sort();
  void topological_sort_visit(Node *x);
  void print_topological_order();
  void DFS_visit(Node *x);
  void print_BFS_path(int j);
  void print_graph();
private:
  int n;
  Node* *vs;
  int *ds;
  int *fs;
  int *parents;
  int *colors; //0:white 1:grey 2:black
  int time;
  Node *head;
};

Graph::Graph(int n_)
{
  n = n_;
  vs = new Node*[n];
  ds = new int[n];   
  fs = new int[n];
  parents = new int[n];
  colors = new int[n];
  time = 0;
  head = NULL;
  for (int i=0; i<n; ++i)
  {
    vs[i] = new Node(i);
    ds[i] = INF;
    fs[i] = INF;
    parents[i] = INF;
    colors[i] = 0;
  }
}

void Graph::add_edge(int i, int j, bool directed=false)
{
  Node *v1 = vs[i];
  Node *v2 = vs[j];
  Node *tmp = new Node(j);
  tmp->next = v1->next;
  v1->next = tmp;
  if (directed == false)
  {
    tmp = new Node(i);
    tmp->next = v2->next;
    v2->next = tmp; 
  }
}

void Graph::BFS(int i)
{
  Node *s = vs[i];
  ds[i] = 0;
  colors[i] = 1;
  queue<int> q;
  q.push(i);
  while (!q.empty())
  {
    Node *v = vs[q.front()];
    q.pop();
    Node *next = v->next;
    while (next != NULL)
    {
      if (colors[next->id] == 0)
      {
        colors[next->id] = 1;
        ds[next->id] = ds[v->id] + 1;
        parents[next->id] = v->id;
        q.push(next->id);
      } 
      next = next->next;
    } 
    colors[v->id] = 2;
  }  
}

void Graph::print_BFS_path(int j)
{
  if (parents[j] == INF)
    cout << j<<' ';
  else
  {
    print_BFS_path(parents[j]);
    cout << j << ' ';
  } 
}

void Graph::DFS()
{
  time = 0; 
  for (int i=0; i<n; ++i)
  {
    if (colors[vs[i]->id] == 0)
      DFS_visit(vs[i]); 
  }  
}

void Graph::DFS_visit(Node *x)
{
  ds[x->id] = ++time;
  colors[x->id] = 1;
  Node *next = x->next;
  while (next != NULL)
  {
    if (colors[next->id] == 0)
    {
      parents[next->id] = x->id;
      DFS_visit(vs[next->id]);
    }
    next = next->next;
  }
  fs[x->id] = ++time;
  colors[x->id] = 2;
}

void Graph::SCC(Node *head)
{
  time = 0;
  Node *p = head;
  int i=0;
  while (p!=NULL)
  {
    if (colors[vs[p->id]->id] == 0)
    {
      cout << "component "<< i++<<": ";
      SCC_visit(vs[p->id]);
      cout << endl;
    }
    p = p->next;
  }
}

void Graph::SCC_visit(Node *x)
{
  colors[x->id] = 1;
  ds[x->id] = ++time;
  cout << x->id << ' ';
  Node *next = vs[x->id]->next;
  while (next != NULL)
  {
    if (colors[next->id] == 0)
    {
      parents[next->id] = x->id;
      SCC_visit(next);
    }
    next = next->next;
  }
  fs[x->id] = ++time;
  colors[x->id] = 2; 
}

Node* Graph::topological_sort()
{
  time = 0;
  for (int i=0; i<n; ++i)
    if (colors[vs[i]->id] == 0)
      topological_sort_visit(vs[i]);
  return head;
}

void Graph::topological_sort_visit(Node *x)
{
  ds[x->id] = ++time;
  colors[x->id] = 1;
  Node *next = x->next;
  while (next != NULL)
  {
    if (colors[next->id] == 0)
    {
      parents[next->id] = x->id;
      topological_sort_visit(vs[next->id]);
    }
    next = next->next;
  }
  colors[x->id] = 2;
  fs[x->id] = ++time;
  if (head == NULL)
    head = new Node(x->id);
  else
  {
    Node *tmp = new Node(x->id);
    tmp->next = head;
    head = tmp;
  }
}

void Graph::print_topological_order()
{
  Node *p = head;
  while (p!=NULL)
  {
    cout << p->id << ' ';
    p = p->next;
  }
  cout << endl;
}

void Graph::print_graph()
{
  for (int i=0; i<n; ++i)
  {
    cout << "i=" << i << ": " << vs[i]->id << "(color="<<colors[vs[i]->id]<<") ";
    Node *next = vs[i]->next;
    while (next != NULL)
    {
      cout << next->id << ' ';
      next = next->next;
    }
    cout << endl;
  }
  cout << "ds="<<' ';
  for (int i=0; i<n; ++i)
    cout << ds[i]<<' ';
  cout << endl;
  cout << "parents="<<' ';
  for (int i=0; i<n; ++i)
    cout << parents[i] << ' ';
  cout << endl;
  cout << "fs="<<' ';
  for (int i=0; i<n; ++i)
    cout << fs[i]<<' ';
  cout << endl;
}

void BFS_test()
{
  Graph graph(8);
  graph.add_edge(0, 1);
  graph.add_edge(0, 4);
  graph.add_edge(1, 5);
  graph.add_edge(2, 5);
  graph.add_edge(2, 6);
  graph.add_edge(2, 3);
  graph.add_edge(3, 6);
  graph.add_edge(3, 7);
  graph.add_edge(5, 6);
  graph.add_edge(6, 7);
  graph.print_graph();
  cout << "BFS(1)"<<endl;
  graph.BFS(1);
  graph.print_graph();
  graph.print_BFS_path(7);
  cout << endl;
}

void DFS_test()
{
  Graph graph(6);
  graph.add_edge(0,1,true);
  graph.add_edge(0,3,true);
  graph.add_edge(1,4,true);
  graph.add_edge(2,4,true);
  graph.add_edge(2,5,true);
  graph.add_edge(3,1,true);
  graph.add_edge(4,3,true);
  graph.add_edge(5,5,true); 
  graph.print_graph();
  cout << "DFS()"<<endl;
  graph.DFS();
  graph.print_graph();
}

void topological_sort_test()
{
  Graph graph(9);
  graph.add_edge(0,1,true);
  graph.add_edge(0,7,true);
  graph.add_edge(1,2,true);
  graph.add_edge(1,7,true);
  graph.add_edge(2,5,true);
  graph.add_edge(3,2,true);
  graph.add_edge(3,4,true);
  graph.add_edge(4,5,true);
  graph.add_edge(6,7,true);
  graph.topological_sort();
  graph.print_topological_order();
}

void SCC_test()
{
  Graph graph(8);
  Graph graph_t(8);
  graph.add_edge(0,1,true);
  graph_t.add_edge(1,0,true);
  graph.add_edge(0,4,true);
  graph_t.add_edge(4,0,true);
  graph.add_edge(1,2,true);
  graph_t.add_edge(2,1,true);
  graph.add_edge(1,4,true);
  graph_t.add_edge(4,1,true);
  graph.add_edge(1,5,true);
  graph_t.add_edge(5,1,true);
  graph.add_edge(2,3,true);
  graph_t.add_edge(3,2,true); 
  graph.add_edge(2,6,true);
  graph_t.add_edge(6,2,true);
  graph.add_edge(3,2,true);
  graph_t.add_edge(2,3,true);
  graph.add_edge(3,7,true);
  graph_t.add_edge(7,3,true);
  graph.add_edge(4,0,true);
  graph_t.add_edge(0,4,true);
  graph.add_edge(4,5,true);
  graph_t.add_edge(5,4,true);
  graph.add_edge(5,6,true);
  graph_t.add_edge(6,5,true);
  graph.add_edge(6,5,true);
  graph_t.add_edge(5,6,true);
  graph.add_edge(6,7,true);
  graph_t.add_edge(7,6,true);
  graph.add_edge(7,7,true);
  graph_t.add_edge(7,7,true);
  Node *head = graph.topological_sort();
  graph_t.SCC(head);
}

int main()
{
  //BFS_test();
  //DFS_test();
  //topological_sort_test();
  SCC_test();
}
