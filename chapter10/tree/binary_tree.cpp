#include <iostream>
#include <stack>
using namespace std;

struct TreeNode
{
  TreeNode():val(0),left(NULL),right(NULL){}
  TreeNode(double val_):val(val_),left(NULL),right(NULL){}
  double val;
  TreeNode *left;
  TreeNode *right;
};

class Tree
{
public:
  Tree():root(NULL){}
  void demo();
  void DLR_recursive();
  void LDR_recursive();
  void LRD_recursive();
  void DLR_mine();
  void DLR();
  void LDR_mine();
  void LDR(){LDR_mine();}
  void LRD_mine();
  void LRD();
private:
  TreeNode *root;
  void dlr_recursive(TreeNode *);
  void ldr_recursive(TreeNode *);
  void lrd_recursive(TreeNode *);
};

void Tree::demo()
{
  root = new TreeNode(18);
  root->left = new TreeNode(12);
  root->left->left = new TreeNode(7);
  root->left->right = new TreeNode(4);
  root->left->right->left = new TreeNode(5);
  root->right = new TreeNode(10);
  root->right->left = new TreeNode(2);
  root->right->right = new TreeNode(21);
}

void Tree::dlr_recursive(TreeNode *p)
{
  if (p == NULL)
    return;
  cout << p->val << ' ';
  dlr_recursive(p->left);
  dlr_recursive(p->right);
}

void Tree::DLR_recursive()
{
  dlr_recursive(root);
  cout << endl;
}

void Tree::ldr_recursive(TreeNode *p)
{
  if (p==NULL)
    return;
  ldr_recursive(p->left);
  cout << p->val << ' ';
  ldr_recursive(p->right);
}

void Tree::LDR_recursive()
{
  ldr_recursive(root);
  cout << endl;
}

void Tree::DLR_mine()
{
  if (root == NULL)
    return;
  stack<TreeNode*> s;
  auto *p = root;
  while (p->left!=NULL)
  {
    cout << p->val << ' ';
    s.push(p);
    p = p->left;
  }
  cout << p->val << ' ';
  s.push(p);
  while (!s.empty())
  {
    auto *p = s.top();
    s.pop();
    p = p->right;
    if (p==NULL)
      continue;
    while (p->left !=NULL)
    {
      cout << p->val << ' ';
      s.push(p);
      p = p->left;
    }
    cout << p->val<<' ';
    s.push(p);
  }
  cout << endl;
}

void Tree::DLR()
{
  auto *p = root;
  stack<TreeNode *> s;
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

void Tree::LDR_mine()
{
  auto *p = root;
  stack<TreeNode *> s;
  while (p!=NULL || !s.empty())
  {
    while (p!=NULL)
    {
      s.push(p);
      p = p->left;
    }
    if (!s.empty())
    {
      p = s.top();
      s.pop();
      cout << p->val << ' ';
      p = p->right;
    }
  }
  cout << endl;
}

void Tree::lrd_recursive(TreeNode *p)
{
  if (p==NULL)
    return;
  lrd_recursive(p->left);
  lrd_recursive(p->right);
  cout << p->val << ' ';
}

void Tree::LRD_recursive()
{
  lrd_recursive(root);
  cout << endl;
}

void Tree::LRD_mine()
{
  auto *p = root;
  stack<TreeNode *> s;
  stack<bool> flags;
  while (p!=NULL || !s.empty())
  {
    while(p!=NULL)
    {
      s.push(p);
      flags.push(false);
      p = p->left;
    }
    if (!s.empty())
    {
      p = s.top();
      auto flag = flags.top();
      flags.pop();
      if (p->right == NULL || flag)
      {
        cout << p->val << ' ';
        s.pop();
        p = NULL;
      }
      else
      {
        flags.push(true);
        p = p->right;
      }
    }
  }
  cout << endl;
}

void Tree::LRD()
{
  auto *p = root;
  TreeNode *r = NULL;
  stack<TreeNode *> s;
  while (p!=NULL || !s.empty())
  {
    while (p!=NULL)
    {
      s.push(p);
      p = p->left;
    }
    if (!s.empty())
    {
      p = s.top();
      if (p->right == NULL || p->right == r)
      {
        s.pop();
        cout << p->val << ' ';
        r = p;
        p = NULL;
      }
      else
        p = p->right;
    }
  }
  cout << endl;
}

int main()
{
  Tree tree;
  tree.demo();
  tree.DLR_recursive();
  tree.DLR_mine();
  tree.DLR();
  tree.LDR_recursive();
  tree.LDR_mine();
  tree.LRD_recursive();
  tree.LRD_mine();
  tree.LRD();
}
