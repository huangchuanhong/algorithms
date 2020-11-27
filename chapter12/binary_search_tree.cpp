#include <iostream>
#include <stack>
using namespace std;

struct Node
{
  Node(double v):val(v),left(NULL),right(NULL),parent(NULL){}
  double val;
  Node *left;
  Node *right;
  Node *parent;
};

class Tree
{
public:
  Tree():root(NULL){}
  void insert(double v);
  Node *search(double v);
  void del(Node *p);
  Node *maximum();
  Node *minimum();
  Node *maximum(Node *);
  Node *minimum(Node *);
  Node *predecessor(Node *p);
  Node *successor(Node *p);
  void inorder_walk();
  void inorder_walk_without_stack();
  void preorder_walk();
  void preorder_walk_without_stack();
  void postorder_walk();
private:
  Node *root;
  void _inorder_walk(Node *p);
  void transplant(Node *u, Node *v);
};

void Tree::insert(double v)
{
  auto *p = root;
  if (p == NULL)
  {
    root = new Node(v);
    return;
  }
  while (p->val != v)
  {
    if (v <= p->val)
    {
      if (p->left == NULL)
      {
        p->left = new Node(v);
        p->left->parent = p;
        return;
      }
      p = p->left;
    }
   else
   {
     if (p->right == NULL)
     {
       p->right = new Node(v);
       p->right->parent = p;
       return;
     }
     p = p->right;
   }
  }  
}

Node *Tree::search(double v)
{
  auto *p = root;
  while (p!=NULL && p->val != v)
  {
    if (v < p->val)
      p = p->left;
    else if (v > p->val)
      p = p->right;
  }
  return p;
}

Node *Tree::minimum(Node *p)
{
  while (p!=NULL && p->left != NULL)
    p = p->left;
  return p;
}

Node *Tree::maximum()
{
  return maximum(root);
}

Node *Tree::minimum()
{
  return minimum(root);
}

Node *Tree::maximum(Node *p)
{
  while (p!=NULL && p->right != NULL)
    p = p->right;
  return p;
}

Node *Tree::predecessor(Node *p)
{
  if (p==NULL)
    return NULL;
  if (p->left != NULL)
    return maximum(p->left);
  while (p->parent != NULL && p->parent->right != p)
    p = p->parent;
  return p->parent; 
}

Node *Tree::successor(Node *p)
{
  if (p == NULL)
    return NULL;
  if (p->right != NULL)
    return minimum(p->right);
  while (p->parent != NULL && p->parent->left != p)
    p = p->parent;
  return p->parent;
}

void Tree::transplant(Node *u, Node *v)
{
  if (u->parent == NULL)
    root = v;
  else if (u->parent->left = u)
    u->parent->left = v;
  else if (u->parent->right = u)
    u->parent->right = v;
  if (v != NULL)
    v->parent = u->parent;
}

void Tree::del(Node *p)
{
  if (p == NULL)
    return;
  if (p->left == NULL)
  {
    transplant(p, p->right); 
    return;
  }
  if (p->right == NULL)
  {
    transplant(p, p->left);
    return;
  }
  auto *q = minimum(p->right);
  if (q != p->right)
  {
    transplant(q, q->right);
    q->right = p->right;
    q->right->parent = q;
  }
  q->left = p->left;
  q->left->parent = q;
  transplant(p, q);
}

void Tree::inorder_walk()
{
  _inorder_walk(root); 
  cout << endl;
}

void Tree::_inorder_walk(Node *p)
{
  if (p==NULL)
    return;
  _inorder_walk(p->left);
  cout << p->val << ' ';
  _inorder_walk(p->right);
}

void Tree::preorder_walk()
{
  auto *p = root;
  stack<Node *> s;
  while (p!=NULL || !s.empty())
  {
    while (p!=NULL)
    {
      cout << p->val << ' ';
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

void Tree::postorder_walk()
{
  auto *p = root;
  Node *r = NULL;
  stack<Node *>s;
  while (p!=NULL || !s.empty())
  {
    while (p!=NULL)
    {
      s.push(p);
      p = p->left;
    }
    p = s.top();
    if (p->right == NULL || p->right == r)
    {
      cout << p->val <<' ';
      s.pop();
      r = p;
      p = NULL;
    }
    else
      p = p->right;
  }
  cout << endl;
}

int main()
{
  Tree t;
  cout << "t.minimum()="<<t.minimum()<<endl;
  cout << "t.maximum()="<<t.maximum()<<endl;
  t.insert(12);
  t.insert(5);
  t.insert(18);
  t.insert(15);
  t.insert(2);
  t.insert(19);
  t.insert(9);
  t.insert(13);
  t.insert(17);
  cout << "inorder_walk"<<endl;
  t.inorder_walk();
  cout << "preorder_walk"<<endl;
  t.preorder_walk();
  cout << "postorder_walk"<<endl;
  t.postorder_walk();
  Node *p = t.search(15);
  cout << "search 15, p->val="<<p->val<<endl;
  p = t.search(100);
  cout << "search 100, p="<<p<<endl;
  cout << "t.minimum()="<<t.minimum()->val<<endl;
  cout << "t.maximum()="<<t.maximum()->val<<endl; 
  p = t.search(2);
  cout << "2's predecessor="<<t.predecessor(p)<<endl;
  p = t.search(5);
  cout << "5's predecessor="<<t.predecessor(p)->val<<endl;
  p = t.search(13);
  cout << "13's predecessor="<<t.predecessor(p)->val<<endl;
  cout << "13's successor="<<t.successor(p)->val<<endl;
  p = t.search(5);
  t.del(p);
  cout << "after del 5"<<endl;
  t.inorder_walk();
  p = t.search(15);
  t.del(p);
  cout << "after del 15"<<endl;
  t.inorder_walk();
}
