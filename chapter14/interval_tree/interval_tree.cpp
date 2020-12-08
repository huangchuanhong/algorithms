#include <iostream>
#include <stack>
using namespace std;

struct Node 
{
  Node():low(0),high(0),max(0),left(NULL),right(NULL),parent(NULL),color(0){}
  Node(double l, double h):low(l),high(h),max(h),left(NULL),right(NULL),parent(NULL),color(1){}
  double low;
  double high;
  double max;
  Node *left;
  Node *right;
  Node *parent;
  bool color;
};

class Tree
{
public:
  Tree():nil(new Node()),root(nil){}
  void insert(Node *x);
  Node *search(double low, double high);
  void del(Node *x);
  void print();
  void init_node(Node *x);
  Node *minimum(Node *x);
  Node *search(Node *x) const;
  Node *nil;
private:
  Node *root;
  void insert_fixup(Node *x);
  void left_rotate(Node *x);
  void right_rotate(Node *x);
  void transplant(Node *u, Node *v);
  void adapt_max_upto_root(Node *x);
  void del_fixup(Node *x);
};

Node *Tree::search(Node *x) const
{
  auto *p = root;
  while (p!=nil)
  {
    if (!((x->high < p->low)||(p->high < x->low)))
      return p;
    if (p->left != nil && p->left->max >= x->low)
      p = p->left;
    else
      p = p->right;
  }
  return p;
}

Node *Tree::search(double low, double high)
{
  auto *p = root;
  while (p!= nil)
  {
    if (p->low == low && p->high == high)
      return p;
    if (low <= p->low)
      p = p->left;
    else
      p = p->right;
  }
  return p;
}
 
void Tree::del_fixup(Node *x)
{
  while (x != root && x->color == 0)
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
        x = y->parent;
      }
      else
      {
        if (y->right->color == 0)
        {
          y->color = 1;
          y->left->color = 0;
          right_rotate(y);
          y = y->parent;
        }
        y->color = x->parent->color;
        x->parent->color = 0;
        left_rotate(y);
        x = root;
      }
    }
    else
    {
      auto *y = x->parent->left;
      if (y->color == 1)
      {
        y->color = 0;
        y->parent->color = 1;
        right_rotate(x->parent);
        y = x->parent->left;
        print();
        cout << endl;
      }
      if (y->left->color == 0 && y->right->color == 0)
      {
        y->color = 1;
        x = y->parent;
      }
      else
      {
        if (y->left->color == 0)
        {
          y->color = 1;
          y->right->color = 0;
          left_rotate(y);
          y = y->parent;
        }
        y->color = x->parent->color;
        x->parent->color = 0;
        right_rotate(y);
        x = root;
      }
    }
  }
  x->color = 0;
}

void Tree::adapt_max_upto_root(Node *x)
{
  while (x!=nil)
  {
    double m = max(max(x->left->max, x->right->max), x->high);
    if (m == x->max)
      return;
    x->max = m;
    x = x->parent;
  }
}

Node *Tree::minimum(Node *x)
{
  Node *q = nil;
  while (x != nil)
  {
    q = x;
    x = x->left;
  }
  return q;
}

void Tree::transplant(Node *x, Node *v)
{
  // x!=nil
  v->parent = x->parent;
  if (x->parent == nil)
    root = v;
  else if (x->parent->left == x)
    v->parent->left = v;
  else
    v->parent->right = v;
}

void Tree::del(Node *x)
{
  bool ori_color = x->color;
  Node *z;
  if (x->left == nil)
  {
    z = x->right;
    transplant(x, x->right);
    adapt_max_upto_root(x->parent);
  }
  else if (x->right == nil)
  {
    z = x->left;
    transplant(x, x->left);
    adapt_max_upto_root(x->parent);
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
      x->right->parent = y;
    }
    else
      y->right->parent = y;
    y->left = x->left;
    y->left->parent = y;
    transplant(x, y);
    y->color = x->color;
    y->max = max(y->max, max(y->left->max, y->right->max));
    adapt_max_upto_root(y->parent);
  }  
  if (ori_color == 0)
    del_fixup(z);
}

void Tree::init_node(Node *x)
{
  x->left = x->right = x->parent = nil;
  x->color = 1;
  x->max = x->high;
}

void Tree::print()
{
  auto *p = root;
  stack<Node *> s;
  while (p!=nil || !s.empty())
  {
    while (p!=nil)
    {
      cout <<'['<<p->low<<','<<p->high<<"], max="<<p->max<<',';
      if (p->color == 0)
        cout << "(black) "<<endl;
      else
        cout << "(red) "<<endl;
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
}

void Tree::left_rotate(Node *x)
{
  auto *y = x->right;
  y->max = x->max;
  x->max = max(max(x->left->max, y->left->max), x->high);
  y->parent = x->parent;
  if (y->parent == nil)
    root = y;
  else if (y->parent->left == x)
    y->parent->left = y;
  else
    y->parent->right = y;
  y->left->parent = x;
  x->right = y->left;
  y->left = x;
  x->parent = y;
}

void Tree::right_rotate(Node *x)
{
  auto *y = x->left;
  y->max = x->max;
  x->max = max(max(x->right->max, y->right->max), x->high);
  y->parent = x->parent;
  if (y->parent == nil)
    root = y;
  else if (y->parent->left = x)
    y->parent->left = y;
  else
    y->parent->right = y;
  y->right->parent = x;
  x->left = y->right;
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
        x->parent->parent->color = 1;
        x = x->parent->parent;
      }
      else
      {
        if (x->parent->right == x)
        {
          x = x->parent;
          left_rotate(x);
        }
        x->parent->parent->color = 1;
        x->parent->color = 0;
        right_rotate(x->parent->parent);
        x = root;
      }
    }
    else
    {
      auto *y = x->parent->parent->left;
      if (y->color == 1)
      {
        x->parent->color = 0;
        y->color = 0;
        x->parent->parent->color = 1;
        x = x->parent->parent;
      }
      else
      {
        if (x->parent->left == x)
        {
          x = x->parent;
          right_rotate(x);
        }
        x->parent->parent->color = 1;
        x->parent->color = 0;
        left_rotate(x->parent->parent);
        x = root;
      }
    }
  }
  root->color = 0;
} 

void Tree::insert(Node *x)
{
  // x.left == x.right == x.parent == nil
  // x.color == 1
  // x.max == x.high
  auto *p = root;
  Node *q = nil;
  while (p!=nil)
  {
    q = p;
    if (x->high > p->max)
      p->max = x->high;
    if (x->low <= p->low)
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
    x->parent = q;
    if (x->low <= q->low)
      q->left = x;
    else
      q->right = x;
    if (q->color == 1)
    {
      insert_fixup(x); 
    }
  }
}


int main()
{
  Tree t;
  Node *x = new Node(16, 21);
  t.init_node(x);
  t.insert(x);
  x = new Node(8,9);
  t.init_node(x);
  t.insert(x);
  x = new Node(25, 30);
  t.init_node(x);
  t.insert(x);
  x = new Node(5, 8);
  t.init_node(x);
  t.insert(x);
  x = new Node(15,23);
  t.init_node(x);
  t.insert(x);
  x = new Node(17, 19);
  t.init_node(x);
  t.insert(x);
  x = new Node(26, 26);
  t.init_node(x);
  t.insert(x);
  x = new Node(0,3);
  t.init_node(x);
  t.insert(x);
  x = new Node(6, 10);
  t.init_node(x);
  t.insert(x);
  x = new Node(19, 20);
  t.init_node(x);
  t.insert(x);
  t.print();  
  //x = t.search(25, 30);
  //x = t.search(17,19);
  //x = t.search(5, 8);
  //cout << x->low << ' ' << x->high<<endl;
  //t.del(x);
  //t.print();
  x = new Node(22, 25);
  t.init_node(x);
  x = t.search(x);
  cout << "x="<<x->low<<' '<<x->high<<endl;
  x = new Node(11, 14);
  t.init_node(x);
  x = t.search(x);
  cout << "x="<<x->low<<' '<<x->high<<endl;

}













