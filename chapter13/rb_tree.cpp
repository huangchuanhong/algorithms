#include <iostream>
#include <stack>
using namespace std;

struct Node
{
  Node():key(0),left(NULL),right(NULL),parent(NULL),color(0){}
  Node(int k):key(k),left(NULL),right(NULL),parent(NULL),color(1){}
  int key;
  Node *left;
  Node *right;
  Node *parent;
  bool color; // red:1, black:0
};

class RBTree
{
public:
  RBTree():nil(new Node()),root(nil){}
  void insert(int key);
  void del(int key);
  Node *minimum(Node *p);
  void print();
private:
  Node *nil;
  Node *root;
  void insert_fixup(Node *p);
  void left_rotate(Node *p);
  void right_rotate(Node *p);
  void transplant(Node *p, Node *q);
  void del_fixup(Node *p);
};

void RBTree::left_rotate(Node *p)
{
  auto *y = p->right;
  y->parent = p->parent;
  if (y->parent == nil)
    root = y;
  else if (y->parent->left == p)
    y->parent->left = y;
  else
    y->parent->right = y;
  p->parent = y;
  p->right = y->left;
  if (p->right != nil)
    p->right->parent = p;
  y->left = p;
}
 
void RBTree::right_rotate(Node *p)
{
  auto *y = p->left;
  y->parent = p->parent;
  if (y->parent == nil)
    root = y;
  else if (y->parent->left == p)
    y->parent->left = y;
  else
    y->parent->right = y;
  p->parent = y;
  p->left = y->right;
  if (p->left != nil)
    p->left->parent = p;
  y->right = p; 
}

void RBTree::insert_fixup(Node *p)
{
  while (p->parent->color == 1)
  {
    if (p->parent->parent->left == p->parent)
    {
      auto *y = p->parent->parent->right;
      if (y->color == 1)
      {
        p->parent->color = 0;
        y->color = 0;
        y->parent->color = 1;
        p = y->parent;
      }
      else
      {
        if (p->parent->right == p)
        {
          p = p->parent;
          left_rotate(p);
        }
        p->parent->color = 0;
        p->parent->parent->color = 1;
        right_rotate(p->parent->parent);
      }
    }
    else if (p->parent->parent->right == p->parent)
    {
      auto *y = p->parent->parent->left;
      if (y->color == 1)
      {
        p->parent->color = 0;
        y->color = 0;
        y->parent->color = 1;
        p = y->parent;
      }
      else
      {
        if (p->parent->left == p)
        {
          p = p->parent;
          right_rotate(p);
        }
        p->parent->color = 0;
        p->parent->parent->color = 1;
        left_rotate(p->parent->parent);
      }
    }
  }
  root->color = 0;
}

void RBTree::insert(int key)
{
  auto *x = root;
  Node *y = nil; 
  while (x != nil)
  {
    y = x;
    if (key < x->key)
      x = x->left;
    else if (key > x->key)
      x = x->right;
    else return;
  }
  Node *p = new Node(key);
  if (y != nil)
  {
    if (key < y->key)
      y->left = p;
    else
      y->right = p;
  }
  else
    root = p;
  p->left = nil;
  p->right = nil;
  p->color = 1;
  p->parent = y;
  insert_fixup(p);
}

void RBTree::transplant(Node *p, Node *q)
{
  q->parent = p->parent;
  if (p->parent == nil)
    root = q;
  else if (p->parent->left == p)
    p->parent->left = q;
  else if (p->parent->right == p)
    p->parent->right = q;
}

Node *RBTree::minimum(Node *p)
{
  auto *q = p;
  Node *u = nil;
  while (q!=nil)
  {
    u = q;
    q = q->left;
  }
  return u;
}

void RBTree::del_fixup(Node *p)
{
  while (p != root && p->color == 0)
  {
    if (p->parent->left == p)
    {
      auto *q = p->parent->right;
      if (q->color == 1)
      {
        p->parent->color = 0;
        q->color = 1;
        left_rotate(p->parent);
        q = p->parent->right;
      }
      if (q->left->color == 0 && q->right->color == 0)
      {
        q->color = 1;
        p = q->parent;
      }
      else
      { 
        if (q->left->color == 1 && q->right->color == 0)
        {
          q->left->color = 0;
          q->color = 1;
          right_rotate(q);
          q = p->parent->right;
        }
        q->color = q->parent->color;
        q->parent->color = 0;
        q->right->color = 0;
        left_rotate(p->parent);
        p = root;
      }
    }
    else if (p->parent->right == p)
    {
      auto *q = p->parent->left;
      if (q->color == 1)
      {
        p->parent->color = 0;
        q->color = 1;
        right_rotate(p->parent);
        q = p->parent->left;
      }
      if (q->left->color == 0 && q->right->color == 0)
      {
        q->color = 1;
        p = q->parent;
      }
     else
     {
       if (q->right->color == 1 && q->left->color == 0)
       {
         q->right->color = 0;
         q->color = 1;
         left_rotate(q);
         q = p->parent->left;
       }
       q->color = q->parent->color;
       q->parent->color = 0;
       q->left->color = 0;
       right_rotate(p->parent);
       p = root;
     }
    }
  }
  root->color = 0;
}

void RBTree::del(int key)
{
  auto *p = root;
  Node *z = nil;
  while (p != nil && p->key != key)
  {
    if (key < p->key)
      p = p->left;
    else
      p = p->right;
  }  
  if (p == nil) return;
  bool p_ori_color = p->color;
  if (p->left == nil)
  {
    z = p->right;
    transplant(p, p->right);
  }
  else if (p->right == nil)
  {
    z = p->left;
    transplant(p, p->left);
  }
  else
  {
    Node *x = minimum(p->right);
    p_ori_color = x->color;
    if (x->parent != p)
    {
      transplant(x, x->right);
      x->right = p->right;
      x->right->parent = x;
    }
    else
      x->right->parent = x; 
    x->left = p->left;
    x->left->parent = x;
    transplant(p, x);
    x->color = p->color;
    z = x->right;
  }
  if (p_ori_color == 0)
    del_fixup(z);
}

void RBTree::print()
{
  auto *p = root;
  stack<Node *> s;
  while (p!=nil || !s.empty())
  {
    while (p!=nil)
    {
      cout << p->key;
      if (p->color == 1)
        cout <<"(red)"<<' ';
      else
        cout <<"(black)"<<' ';
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

int main()
{
  RBTree t;
  t.insert(1);
  t.insert(2);
  t.insert(3);
  t.print();
  t.insert(4);
  t.print();
  t.insert(5);
  t.print();
  t.insert(6);
  t.print();
  t.insert(7);
  t.insert(8);
  t.insert(9);
  t.print();
  //t.del(5);
  t.del(2);
  t.print();
}
