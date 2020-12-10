#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

struct Node
{
  Node(string s, int c):item(s),count(c),left(NULL),right(NULL){}
  string item;
  int count;
  Node *left;
  Node *right;
};

class MinHeap
{
public: 
  MinHeap(vector<Node*> n);
  Node* minimum();
  void insert(Node *);
  void fix(int i);
  void print();
  bool empty();
  int size;
private:
  int capacity;
  vector<Node*> nodes;
};

bool MinHeap::empty()
{
  if (size == 0)
    return true;
  else return false;
}

void MinHeap::insert(Node *x)
{
  if (capacity > size)
    nodes[++size] = x;
  else 
  {
    nodes.push_back(x);
    ++size;
    ++capacity;
  }
  int i = size;
  while (i/2 >=1 && x->count < nodes[i/2]->count)
  {
    nodes[i] = nodes[i/2];
    i = i/2;
  }
  nodes[i] = x;
}

Node* MinHeap::minimum()
{
  auto *node = nodes[1];
  nodes[1] = nodes[size--];
  fix(1);
  return node;
}

void MinHeap::fix(int i)
{
  auto* cur = nodes[i];
  int n = size;
  while (i<=n)
  {
    int left = 2 * i;
    int right = 2 * i + 1;
    int tmp;
    if (left <=n)
    {
      tmp = left;
      if (right <=n && nodes[tmp]->count > nodes[right]->count)
        tmp = right;
      if (cur->count > nodes[tmp]->count)
      {
        nodes[i] = nodes[tmp];
        i = tmp;
      }
      else
      {
        nodes[i] = cur;
        break;
      }
    }
    else
    {
      nodes[i] = cur;
      break;
    }
  }
}

MinHeap::MinHeap(vector<Node*> n)
{
  nodes.push_back(NULL);
  for (int i=0; i<n.size(); ++i)
    nodes.push_back(n[i]);
  size = nodes.size() - 1;
  capacity = nodes.size() - 1;
  for (int i=size/2; i>=1; --i)
    fix(i); 
}

void MinHeap::print()
{
  for (int i=1; i<=size; ++i)
    cout << nodes[i]->count <<' ';
  cout <<endl;
}

void print_huffman(Node *root)
{
  auto *p = root;
  stack<Node *> s;
  while (p!=NULL || !s.empty())
  {
    while(p!=NULL)
    {
      cout << p->item<<"("<<p->count<<") ";
      s.push(p);
      p = p->left;
    }
    if (!s.empty())
    {
      p = s.top();
      s.pop();
      p = p->right;
    }
  }
  cout << endl;
}

void huffman(const vector<string> &items, const vector<int> &counts)
{
  vector<Node*> nodes;
  for (int i=0; i<items.size(); ++i)
  {
    Node *x = new Node(items[i], counts[i]);
    nodes.push_back(x);
  }
  MinHeap heap(nodes);
  while (heap.size >=2)
  {
    auto *x = heap.minimum();
    auto *y = heap.minimum();
    Node *z = new Node("", x->count + y->count);
    z->left = x;
    z->right = y;
    heap.insert(z);
  }
  print_huffman(heap.minimum());
}

int main()
{
  vector<int> counts{45,13,12,16,9,5};
  vector<string> items{"a","b","c","d","e","f"};
  huffman(items, counts);
}
