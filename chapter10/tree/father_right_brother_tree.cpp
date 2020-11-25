// page 138 10.4-4
#include <iostream>
#include <stack>
using namespace std;

struct Node
{
  Node():val(0),father(NULL),rbrother(NULL),lchild(NULL){}
  Node(double val_):val(val_),father(NULL),rbrother(NULL),lchild(NULL){}
  double val;
  Node *father;
  Node *rbrother;
  Node *lchild;
};

class Tree
{
public:
  Tree():root(NULL){}
  void demo();
  void tranverse();
private:
  Node *root;
  void _tranverse(Node *p);
};

void Tree::demo()
{
  root = new Node(1);
  root->lchild = new Node(2);
  root->lchild->father = root;
  root->lchild->rbrother = new Node(3);
  root->lchild->rbrother->father = root;
  root->lchild->rbrother->rbrother = new Node(4);
  root->lchild->rbrother->rbrother->father = root;
  auto *p = root->lchild;
  p->lchild = new Node(5);
  p->lchild->father = p;
  p->lchild->rbrother = new Node(6);
  p->lchild->rbrother->father = p;
  
  p = root->lchild->rbrother;
  p->lchild = new Node(7);
  p->lchild->father = p;
  p->lchild->rbrother = new Node(8);
  p->lchild->rbrother->father = p;
  p->lchild->rbrother->rbrother = new Node(9);
  p->lchild->rbrother->rbrother->father = p;
  p->lchild->rbrother->rbrother->rbrother = new Node(10);
  p->lchild->rbrother->rbrother->rbrother->father = p;
  
  p = root->lchild->rbrother->rbrother;
  p->lchild = new Node(11);
  p->lchild->father = p;
  
  p = root->lchild->lchild->rbrother;
  p->lchild = new Node(12);
  p->lchild->father = p;
  
  p = root->lchild->rbrother->lchild->rbrother->rbrother;
  p->lchild = new Node(13);
  p->lchild->father = p;
  p->lchild->rbrother = new Node(14);
  p->lchild->rbrother->father = p;
}

void Tree::tranverse()
{
  _tranverse(root);
  cout << endl;
}

void Tree::_tranverse(Node *p)
{
  if (p==NULL)
    return;
  cout << p->val<< ' ';
  p = p->lchild;
  while (p != NULL)
  {
    _tranverse(p);
    p = p->rbrother;
  } 
}

int main()
{
  Tree t;
  t.demo();
  t.tranverse();
}





































