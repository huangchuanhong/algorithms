#include <iostream>
#include <stack>
#include "order_statistic_tree.h"
using namespace std;

//struct Node 
//{
//  Node():key(0),size(0),left(NULL),right(NULL),parent(NULL),color(0){}
//  Node(int k):key(k),size(1),left(NULL),right(NULL),parent(NULL),color(1){}
//  void init(Node *x);
//  int key;
//  int size;
//  Node *left;
//  Node *right;
//  Node *parent;
//  bool color; // block:0, red: 1
//};
//
//class Tree
//{
//public:
//  Tree():nil(new Node()),root(nil){}
//  void insert(Node *x);
//  Node *search(int key);
//  void del(Node *x);
//  Node *select(int i);
//  int key_rank(int key);
//  int key_rank_recursive(int key);
//  int rank(Node *p);
//  void print();
//  void init_node(Node *x);
//  Node *minimum(Node *x);
//  Node *nil;
//private:
//  Node *root;
//  void insert_fixup(Node *x);
//  void left_rotate(Node *x);
//  void right_rotate(Node *x);
//  void minus1_upto_root(Node *x);
//  void transplant(Node *u, Node *v);
//  void del_fixup(Node *x);
//  int _key_rank_recursive(int key, Node *p);
//};

int Tree::_key_rank_recursive(int key, Node *p)
{
  if (p == nil)
    return -1;
  if (key == p->key)
    return p->left->size + 1;
  if (key < p->key)
    return _key_rank_recursive(key, p->left);
  else
  {
    int r = _key_rank_recursive(key, p->right);
    if (r == -1)
      return -1;
    else
      return p->left->size + 1 + r;
  }
}

int Tree::key_rank_recursive(int key)
{
  int r = _key_rank_recursive(key, root);
  
}

int Tree::key_rank(int key)
{
  auto *p = root;
  int r = 0;
  while (p!=nil && p->key != key)
  {
    if (key < p->key)
      p = p->left;
    else
    {
      r += p->left->size + 1;
      p = p->right;
    }
  }
  if (p != nil)
    r += p->left->size + 1;
  else
    r = -1;
  return r;
}

Node *Tree::select(int i)
{
  auto *p = root;
  while (p != nil)
  {
    int r = p->left->size + 1;
    if (i == r)
      return p;
    if (i < r)
      p = p->left;
    else
    {
      i -= r;
      p = p->right;
    }
  }
  return p;
}

int Tree::rank(Node *p)
{
  // p != nil
  auto *q = p;
  int r = q->left->size + 1;
  while (q != root)
  {
    if (q->parent->right == q)
      r += q->parent->left->size + 1;
    q = q->parent;
  }
  return r;
}

void Tree::init_node(Node *x)
{
  x->size = 1;
  x->left = x->right = x->parent = nil;
  x->color = 1;
}

void Tree::left_rotate(Node *x)
{
  // x->right != nil
  auto *y = x->right;
  y->size = x->size;
  x->size = x->left->size + y->left->size + 1;
  y->parent = x->parent;
  if (y->parent == nil)
    root = y;
  else if (y->parent->left == x)
    y->parent->left = y;
  else
    y->parent->right = y;
  x->right = y->left;
  y->left->parent = x;
  y->left = x;
  x->parent = y;
}

void Tree::right_rotate(Node *x)
{
  // x->left != nil
  auto *y = x->left;
  y->size = x->size;
  x->size = x->right->size + y->right->size + 1;
  y->parent = x->parent;
  if (y->parent == nil)
    root = y;
  else if (y->parent->left == x)
    y->parent->left = y;
  else
    y->parent->right = y;
  x->left = y->right;
  y->right->parent = x;
  y->right = x;
  x->parent = y;
}

void Tree::insert_fixup(Node *x)
{
  while (x != root && x->parent->color == 1)
  {
    if (x->parent->parent->left == x->parent)
    {
      auto *y = x->parent->parent->right;
      if (y->color == 1)
      {
        x->parent->color = 0;
        y->color = 0;
        y->parent->color = 1;
        x = y->parent;
      }
      else
      {
        if (x->parent->right == x)
        {
          x = x->parent;
          left_rotate(x);
        }
        x->parent->color = 0;
        x->parent->parent->color = 1;
        right_rotate(x->parent->parent);
      }
    }
    if (x->parent->parent->right == x->parent)
    {
      auto *y = x->parent->parent->left;
      if (y->color == 1)
      {
        x->parent->color = 0;
        y->color = 0;
        y->parent->color = 1;
        x = y->parent;
      }
      else
      {
        if (x->parent->left == x)
        {
          x = x->parent;
          right_rotate(x);
        }
        x->parent->color = 0;
        x->parent->parent->color = 1;
        left_rotate(x->parent->parent);
      }
    }
  }
  root->color = 0;
}

void Tree::insert(Node *x)
{
  // x->left = nil;
  // x->right = nil;
  // x->parent = nil;
  // x->size = 1;
  // x->color = 1;
  auto *p = root;
  Node *q = nil;
  while (p!=nil)
  {
    q = p;
    p->size += 1;
    if (x->key <= p->key)
      p = p->left;
    else
      p = p->right;
  }
  if (q == nil)
  {
    root = x;
    x->color = 0;
  }
  else
  {
    if (x->key <= q->key)
      q->left = x;
    else
      q->right = x;
    x->parent = q;
    if (q->color == 1)
      insert_fixup(x);
  }
}

void Tree::print()
{
  auto *p = root;
  stack<Node *> s;
  while (p!=nil || !s.empty())
  {
    while (p!=nil)
    {
      s.push(p);
      p = p->left;
    }
    if (!s.empty())
    {
      p = s.top();
      s.pop();
      cout << p->key << "(size:"<<p->size<<", ";
      if (p->color == 1)
        cout << "red) ";
      else
        cout << "black) ";
      p = p->right;
    }
  }
  cout << endl;
}
 
Node *Tree::search(int key)
{
  auto *p = root;
  while (p!=nil && p->key != key)
  {
    if (key < p->key)
      p = p->left;
    else
      p = p->right;
  } 
  return p;
}

void Tree::minus1_upto_root(Node *p)
{
  while (p != nil)
  {
    --p->size;
    p = p->parent;
  }
}

void Tree::transplant(Node *u, Node *v)
{
  // u != nil
  v->parent = u->parent;
  if (v->parent == nil)
    root = v;
  else if (v->parent->left == u)
  {
    v->parent->left = v;
  }
  else
    v->parent->right = v;
}

Node *Tree::minimum(Node *p)
{
  Node *q = nil;
  while (p!=nil)
  {
    q = p;
    p = p->left;
  }
  return q;
}

void Tree::del_fixup(Node *x)
{
  while (x!=root && x->color == 0)
  {
    if (x->parent->left == x)
    {
      auto *y = x->parent->right;
      if (y->color == 1)
      {
        y->color = 0;
        y->parent->color = 1;
        left_rotate(x->parent);
        y = x->parent->right;
      }
      if (y->left->color == 0 && y->right->color == 0)
      {
        y->color = 1;
        x = x->parent;
      }
      else 
      {
        if (y->right->color == 0)
        {
          y->color = 1;
          y->left->color = 0;
          right_rotate(y);
          y = x->parent->right;
        }
        y->color = y->parent->color;
        y->parent->color = 0;
        y->right->color = 0;
        left_rotate(y->parent);
        x = root;
      }
    }
    if (x->parent->right == x)
    {
      auto *y = x->parent->left;
      if (y->color == 1)
      {
        y->color = 0;
        y->parent->color = 1;
        right_rotate(x->parent);
        y = x->parent->left;
      }
      if (y->left->color == 0 && y->right->color == 0)
      {
        y->color = 1;
        x = x->parent;
      }
      else
      {
        if (y->left->color == 0)
        {
          y->color = 1;
          y->right->color = 0;
          left_rotate(y);
          y = x->parent->right;
        }
        y->color = y->parent->color;
        y->parent->color = 0;
        y->left->color = 0;
        right_rotate(y->parent);
        x = root;
      }
    }
  }
  x->color = 0;
}
 
void Tree::del(Node *x)
{
  bool ori_color = x->color;
  Node *z;
  if (x->left == nil)
  {
    z = x->right;
    transplant(x, x->right);
    minus1_upto_root(x->parent); 
  }
  else if (x->right == nil)
  {
    z = x->left;
    transplant(x, x->left);
    minus1_upto_root(x->parent);
  }
  else
  {
    auto *y = minimum(x->right);
    z = y->right;
    ori_color = y->color;
    if (y->parent != x)
    {
      transplant(y, y->right);
      y->right = x->right;
      y->right->parent = y;
    }
    else
      z->parent = y;
    y->left = x->left;
    y->left->parent = y;
    y->color = x->color;
    y->size = x->size;
    transplant(x, y);
    minus1_upto_root(z->parent);
  }
  if (ori_color == 0)
    del_fixup(z);
}

//int main()
//{
//  Tree t;
//  Node *x;
//  for (int i=1; i<=9; ++i)
//  {
//    x = new Node(i);
//    t.init_node(x);
//    t.insert(x);
//    t.print();
//  }
//  int r = t.key_rank(7);
//  cout << "rank(7)="<<r<<endl;
//  cout << "rank(7)="<<t.key_rank_recursive(7)<<endl;
//  r = t.key_rank(11);
//  cout << "rank(11)="<<r<<endl;
//  cout << "rank(11)="<<t.key_rank_recursive(11)<<endl;
//  x = t.search(10);
//  cout << x->key << endl;
//  x = t.search(11);
//  if (x == t.nil)
//    cout << "nil"<<endl;
//  else
//    cout << "not nil"<<endl;
//  //x = t.search(6);
//  //t.del(x);
//  x = t.search(8);
//  t.del(x);
//  t.print();
//  x = t.select(1);
//  cout << x->key<<endl;
//  x = t.select(5);
//  cout << x->key <<endl;
//  cout << t.rank(x)<<endl;
//  x = t.select(8);
//  cout << t.rank(x)<<endl;
//}
