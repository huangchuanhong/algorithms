#include <iostream>
#include <math.h>
#include <queue>
using namespace std;

const int INF = 100000000;

struct Node
{
  Node(int k):degree(0),key(k),mark(false),parent(NULL),left(NULL),right(NULL),child(NULL){}
  int degree;
  int key;
  bool mark;
  Node *parent;
  Node *left;
  Node *right;
  Node *child;
};

class FibHeap
{
public:
  FibHeap();
  void insert(Node *x);
  void Union(FibHeap* F1, FibHeap* F2);
  Node *extract_min();
  void decrease_key(Node *x, int key);
  void del(Node *x);
  void print();
  void extract_min_demo_heap();
  void decrease_key_demo_heap();
  Node *min;
private:
  void cut(Node *x);
  void cascading_cut(Node *y);
  void consolidate();
  //Node *min;
  int n;
};

FibHeap::FibHeap()
{
  min = NULL;
  n = 0;
}

void FibHeap::insert(Node *x)
{
  if (min == NULL)
  {
    min = x;
    x->degree = 0;
    x->mark = false;
    x->left = x->right = x;
    x->parent = NULL;
    x->child = NULL;
  }
  else
  {
    x->degree = 0;
    x->mark = false;
    x->left = min->left;
    x->left->right = x;
    x->right = min;
    min->left = x;
    if (x->key < min->key)
      min = x;
    x->parent = NULL;
    x->child = NULL;
  }
  ++n;
}

void FibHeap::Union(FibHeap* F1, FibHeap* F2)
{
  if (F1->min == NULL && F2->min == NULL)
    return;
  if (F1->min == NULL && F2->min != NULL)
  {
    min = F2->min;
    n = F2->n;
    F2->min = NULL;
    F2->n = 0;
    return;
  }
  if (F1->min != NULL && F2->min == NULL)
  {
    min = F1->min;
    n = F1->n;
    F1->min = NULL;
    F1->n = 0;
    return;
  }
  min = F1->min;
  while (F2->min->left != F2->min)
  {
    Node *z = F2->min->left;
    F2->min->left = z->left;
    z->left = min->left;
    min->left->right = z;
    z->right = min;
    min->left = z;
  }
  Node *z = F2->min;
  z->left = min->left;
  min->left->right = z;
  z->right = min;
  min->left = z;
  if (min->key > z->key)
    min = z;
  n = F1->n + F2->n;
  F1->min = NULL;
  F1->n = 0;
  F2->min = NULL;
  F2->n = 0;
}

Node* FibHeap::extract_min()
{
  if (min == NULL)
    return NULL;
  if (min->child == NULL)
  {
    if (min->right == min)
    {
      Node *r = min;
      n = 0;
      min = NULL;
      return r;
    }
    else
    {
      min->right->left = min->left;
      min->left->right = min->right;
      Node *ret = min;
      min = min->right;
      Node *r = min;
      --n; //n
      consolidate();
      return ret;
    }
  }
  if (min->right == min)
  {
    Node *ret = min;
    min = min->child;
    min->parent = NULL;
    min->mark = false;
    Node *left = min->left;
    while (left!=min)
    {
      left->parent = NULL;
      min->mark = false;
    } 
    --n;
    return ret;
  }
  Node *ret = min;
  min = min->right;
  min->left = ret->left;
  ret->left->right = min;
  Node *child = ret->child;
  while (child->left != child)
  {
    Node *tmp = child->left;
    child->left = tmp->left;
    tmp->right = min;
    tmp->left = min->left;
    tmp->left->right = tmp;
    min->left = tmp;
    tmp->parent = NULL;
    tmp->mark = false;
  }
  Node *tmp = child;
  tmp->right = min;
  tmp->left = min->left;
  tmp->left->right = tmp;
  min->left = tmp;
  tmp->parent = NULL;
  tmp->mark = false;
  --n;
  consolidate();
  return ret;
}

void FibHeap::consolidate()
{
  int N = log(n) / log((1+sqrt(5))/2)+1; 
  Node* *A = new Node*[N];
  for (int i=0; i<N; ++i)
    A[i] = NULL;
  while (min->left != min)
  {
    Node *x = min->left;
    min->left = x->left;
    int d = x->degree;
    while (A[d]!=NULL)
    {
      auto *y = A[d];
      if (y->key < x->key)
        swap(x, y);
      y->parent = x;
      y->mark = false;
      if (x->child)
      {
        y->right = x->child;
        y->left = x->child->left;
        y->left->right = y;
        x->child->left = y;
      }
      else
      {
        x->child = y;
        y->left = y;
        y->right = y;
      }
      ++x->degree;
      A[d] = NULL;
      ++d;
    }
    A[d] = x;
  }
  Node *x = min;
  int d = x->degree;
  while (A[d]!=NULL)
  {
    auto *y = A[d];
    if (y->key < x->key)
      swap(x, y);
    y->parent = x;
    y->mark = false;
    if (x->child)
    {
      y->right = x->child;
      y->left = x->child->left;
      x->child->left->right = y;
      x->child->left = y;
    }
    else
    {
      x->child = y;
      y->left = y;
      y->right = y;
    }
    ++x->degree;
    A[d] = NULL;
    ++d;
  }
  A[d] = x;
  min = NULL;
  for (int i=0; i<N; ++i)
  {
    if (A[i]!=NULL)
    {
      if (min == NULL)
      {
        min = A[i];
        min->left = min;
        min->right = min;
        min->parent = NULL; 
      }
      else
      {
        A[i]->left = min->left;
        A[i]->left->right = A[i];
        A[i]->right = min;
        min->left = A[i];
        if (A[i]->key < min->key)
          min = A[i];
      }
    }
  }
  delete[] A;
}

void FibHeap::decrease_key(Node *x, int key)
{
  if (x->parent == NULL)
  {
    x->key = key;
    if (x->key < min->key)
      min = x;
    return;
  }
  Node *y = x->parent;
  x->key = key;
  if (x->key < y->key)
  {
    cut(x);
    cascading_cut(y);
  }
  if (x->key < min->key)
    min = x;
}

void FibHeap::cut(Node *x)
{
  Node *y = x->parent;
  // y
  --y->degree;
  if (x->right == x)
    y->child = NULL;
  else 
  {
    if (y->child == x)
      y->child = x->right;
    x->right->left = x->left;
    x->left->right = x->right;
  }
  // x
  x->mark = false;
  x->parent = NULL;
  x->right = min;
  x->left = min->left;
  x->left->right = x;
  min->left = x;
}

void FibHeap::cascading_cut(Node *y)
{
  Node *z = y->parent;
  if (z == NULL)
    return;
  if (y->mark == false)
  {
    y->mark = true;
    return;
  }
  cut(y);
  cascading_cut(z);
}

void FibHeap::del(Node *x)
{
  decrease_key(x, -INF); 
  extract_min();
}

void FibHeap::print()
{
  if (min == NULL)
    return;
  queue<Node*> q;
  cout << "root="<<min->key;
  if (min->mark)
    cout << "(mark) ";
  else
    cout << ' ';
  q.push(min);
  auto *x = min->left;
  while (x != min)
  {
    cout << x->key;
    if (x->mark)
      cout << "(mark) ";
    else
      cout << ' ';
    q.push(x);
    x = x->left;
  }
  cout << endl;
  while (!q.empty())
  {
    auto *x = q.front();
    q.pop();
    if (x->child != NULL)
    {
      auto *child = x->child;
      cout << x->key<<"'s child="<<' ';
      cout << child->key;
      if (child->mark)
        cout << "(mark) ";
      else
        cout << ' ';
      q.push(child);
      auto *y = child->left;
      while (y!=child)
      {
        cout << y->key;
        if (y->mark)
          cout << "(mark) ";
        else
          cout << ' ';
        q.push(y);
        y = y->left;
      }
      cout << endl;
    } 
  }
}

void FibHeap::extract_min_demo_heap()
{
  // 23
  Node *x_23 = new Node(23);
  // 7
  Node *x_7 = new Node(7);
  // 21
  Node *x_21 = new Node(21); 
  // 3
  Node *x_3 = new Node(3);
  x_3->degree = 3;
  // 17
  Node *x_17 = new Node(17);
  x_17->degree = 1;
  // 24
  Node *x_24 = new Node(24);
  x_24->degree = 2;
  // root_list
  min = x_3;
  x_3->left = x_21;
  x_21->right = x_3;
  x_21->left = x_7;
  x_7->right = x_21;
  x_7->left = x_23;
  x_23->right = x_7;
  x_23->left = x_24;
  x_24->right = x_23;
  x_24->left = x_17;
  x_17->right = x_24;
  x_17->left = x_3;
  x_3->right = x_17;
  // 18
  Node *x_18 = new Node(18);
  x_18->degree = 1;
  x_18->mark = true;
  x_18->parent = x_3;
  // 52
  Node *x_52 = new Node(52);
  x_52->parent = x_3;
  // 38
  Node *x_38 = new Node(38);
  x_38->degree = 1; 
  x_38->parent = x_3;
  // 3_child list
  x_3->child = x_38;
  x_38->left = x_52;
  x_52->right = x_38;
  x_52->left = x_18;
  x_18->right = x_52;
  x_18->left = x_38;
  x_38->right = x_18;
  // 30
  Node *x_30 = new Node(30);
  x_30->parent = x_17;
  // x_17 child list
  x_17->child = x_30;
  x_30->left = x_30;
  x_30->right = x_30;
  // 26
  Node *x_26 = new Node(26);
  x_26->mark = true;
  x_26->parent = x_24;
  // 46
  Node *x_46 = new Node(46);
  x_46->parent = x_24;
  // x_24 child list
  x_24->child = x_26;
  x_26->left = x_46;
  x_46->right = x_26;
  x_46->left = x_26;
  x_26->right = x_46;
  // 39
  Node *x_39 = new Node(39);
  x_39->mark = true;
  x_39->parent = x_18;
  // x_18 child list
  x_18->child = x_39;
  x_39->left = x_39;
  x_39->right = x_39;
  // 41
  Node *x_41 = new Node(41);
  x_41->parent = x_38;
  // x_38 child list
  x_38->child = x_41;
  x_41->left = x_41;
  x_41->right = x_41;
  // 35
  Node *x_35 = new Node(35);
  x_35->parent = x_26;
  // x_26 child list
  x_26->child = x_35;
  x_35->left = x_35;
  x_35->right = x_35;
  n = 15;
}

void FibHeap::decrease_key_demo_heap()
{
  // 7
  Node *x_7 = new Node(7);
  x_7->degree = 3;
  // 18
  Node *x_18 = new Node(18);
  x_18->degree = 2;
  x_18->mark = true;
  // 38
  Node *x_38 = new Node(38);
  x_38->degree = 1;
  // root list
  min = x_7;
  x_7->left = x_38;
  x_38->right = x_7;
  x_38->left = x_18;
  x_18->right = x_38;
  x_18->left = x_7;
  x_7->right = x_18;
  // 24
  Node *x_24 = new Node(24);
  x_24->degree = 2;
  x_24->parent = x_7;
  // 17
  Node *x_17 = new Node(17);
  x_17->degree = 1;
  x_17->parent = x_7;
  // 23
  Node *x_23 = new Node(23);
  x_23->parent = x_7;
  // x_7 child list
  x_7->child = x_23;
  x_23->left = x_17;
  x_17->right = x_23;
  x_17->left = x_24;
  x_24->right = x_17;
  x_24->left = x_23;
  x_23->right = x_24;
  // 21
  Node *x_21 = new Node(21);
  x_21->degree = 1;
  x_21->parent = x_18;
  // 39
  Node *x_39 = new Node(39);
  x_39->parent = x_18;
  x_39->mark = true;
  // x_18 child list
  x_18->child = x_39;
  x_39->left = x_21;
  x_21->right = x_39;
  x_21->left = x_39;
  x_39->right = x_21;
  // 41
  Node *x_41 = new Node(41);
  x_41->parent = x_38;
  // x_38 child list
  x_38->child = x_41;
  x_41->left = x_41;
  x_41->right = x_41;
  // 26
  Node *x_26 = new Node(26);
  x_26->degree = 1;
  x_26->mark = true;
  x_26->parent = x_24;
  // 46
  Node *x_46 = new Node(46);
  x_46->parent = x_24;
  // x_24 child list
  x_24->child = x_46;
  x_46->left = x_26;
  x_26->right = x_46;
  x_26->left = x_46;
  x_46->right = x_26;
  // 30
  Node *x_30 = new Node(30);
  x_30->parent = x_17;
  // x_17 child list
  x_17->child = x_30;
  x_30->left = x_30;
  x_30->right = x_30;
  // 52
  Node *x_52 = new Node(52);
  x_52->parent = x_21;
  // x_21 child list
  x_21->child = x_52;
  x_52->left = x_52;
  x_52->right = x_52;
  // 35
  Node *x_35 = new Node(35);
  x_35->parent = x_26;
  // x_26 child list
  x_26->child = x_35;
  x_35->left = x_35;
  x_35->right = x_35;
  n = 14;
}

void fib_extract_min_test()
{
  FibHeap fh;
  fh.extract_min_demo_heap();
  cout << "before extract min"<<endl;
  fh.print();
  cout << endl;
  fh.extract_min();
  cout << "after extract min"<<endl;
  fh.print();
}

void fib_decrease_key_test()
{
  FibHeap fh;
  fh.decrease_key_demo_heap();
  fh.print();
  cout << endl;
  Node *x = fh.min->child->right->child;
  int ori_key = x->key;
  fh.decrease_key(x, 15);
  cout << "after decrease "<<ori_key<<" to "<< 15<<endl;
  fh.print();
  x = fh.min->child->right->child->child;
  ori_key = x->key;
  fh.decrease_key(x, 5);
  cout << "after decrease "<<ori_key<<" to "<<5<<endl;
  fh.print();
}

int main()
{
  //fib_extract_min_test();
  fib_decrease_key_test();
}
