#include <iostream>
#include <queue>
using namespace std;

const int t = 2;

struct Node
{
  int n;
  bool leaf;
  char key[2*t-1];
  Node* c[2*t];
};

void init_node(Node *node)
{
  node->n = 0;
  node->leaf = 1;
}

void disk_read(Node *node){}
void disk_write(Node *node){}

class BTree
{
public:
  BTree(){root=new Node(); init_node(root);}
  pair<Node*, int> search(char key);
  void insert(char key);
  void del(char key); 
  char minimum(Node *node);
  char maximum(Node *node);
  void print();
  Node* get_root(){return root;}
private:
  void _del(Node*, char);
  pair<Node*, int> _search(Node*, char);
  void split_child(Node *x, int i);
  void insert_nonefull(Node *x, char key);
  Node *root;
};

void BTree::_del(Node* x, char key)
{
  if (x->leaf)
  {
    int i;
    for (i=0; i<x->n&&key>x->key[i]; ++i);
    if (i<x->n&&key==x->key[i])
    {
      for (int j=i; j<=x->n-2; ++j)
        x->key[j] = x->key[j+1];
      --x->n;
      disk_write(x);
    }
    else
    {
      return;  
    }
  }
  else
  {
    int i;
    for (i=0; i<x->n&&key>x->key[i];++i);
    if (i<x->n&&key==x->key[i])
    {
      if (x->c[i]->n > t-1)
      {
        char pre_x = maximum(x->c[i]);
        x->key[i] = pre_x;
        _del(x->c[i], pre_x);
      }
      else if (x->c[i+1]->n > t-1)
      {
        char post_x = minimum(x->c[i+1]);
        x->key[i] = post_x;
        _del(x->c[i+1], post_x);
      }
      else
      {
        // x->c[i]
        x->c[i]->n = 2*t-1;
        x->c[i]->key[t-1] = key;
        for (int j=0; j<t-1; ++j)
          x->c[i]->key[t+j] = x->c[i+1]->key[j];
        if (!x->c[i]->leaf)
        {
          for (int j=0; j<t; ++j)
            x->c[i]->c[t+j] = x->c[i+1]->c[j];
        }
        disk_write(x->c[i]);
        // x
        for (int j=i; j<x->n; ++j)
          x->key[j] = x->key[j+1];
        --x->n;
        auto y = x->c[i+1];
        for (int j=i+1; j<x->n; ++j)
          x->c[j] = x->c[j+1];
        disk_write(x);
        // x->c[i+1]
        delete y;
      }
    }
    else
    {
      if (x->c[i]->n > t-1)
      {
        _del(x->c[i], key);
      }
      else
      {
        // c[i-1]->n > t-1
        if (i-1 >=0 && x->c[i-1]->n > t-1)
        {
          // change c[i]
          for (int j=t-2; j>=0; --j)
            x->c[i]->key[j+1] = x->c[i]->key[j];
          x->c[i]->key[0] = x->key[i-1];
          if (!x->c[i]->leaf)
          {
            for (int j=t-1; j>=0; --j)
              x->c[i]->c[j+1] = x->c[i]->c[j];
            x->c[i]->c[0] = x->c[i-1]->c[x->c[i-1]->n];
          }
          ++x->c[i]->n;
          disk_write(x->c[i]);
          // change x
          x->key[i-1] = x->c[i-1]->key[x->c[i-1]->n-1];
          disk_write(x);
          // change c[i-1]
          --x->c[i-1]->n;
          disk_write(x->c[i-1]);
          // recursive
          _del(x->c[i], key);
        }
        // c[i+1]->n > t-1
        else if (i<x->n && x->c[i+1]->n > t-1)
        {
          // change c[i]
          ++x->c[i]->n;
          x->c[i]->key[t-1] = x->key[i];
          if (!x->leaf)
            x->c[i]->c[t] = x->c[i+1]->c[0];
          disk_write(x->c[i]);
          // chage x
          x->key[i] = x->c[i+1]->key[0];
          disk_write(x);
          // chage c[i+1]
          for (int j=1; j<=x->c[i+1]->n-1; ++j)
            x->c[i+1]->key[j-1] = x->c[i+1]->key[j];
          if (!x->c[i+1]->leaf)
          {
            for (int j=1; j<=x->c[i+1]->n; ++j)
              x->c[i+1]->c[j-1] = x->c[i+1]->c[j];
          }
          --x->c[i+1]->n;
          disk_write(x->c[i+1]);
          // recursive
          _del(x->c[i],key);
        }
        else
        {
          if (i>1)
          {
            // change c[i-1]
            x->c[i-1]->n = 2*t-1;
            x->c[i-1]->key[t-1] = x->key[i-1];
            for (int j=0; j<t-1; ++j)
              x->c[i-1]->key[j+t] = x->c[i]->key[j];
            if (!x->leaf)
            {
              for (int j=0; j<t; ++j)
                x->c[i-1]->c[j+t] = x->c[i]->c[j];
            }
            disk_write(x->c[i-1]);
            // change x
            auto *y = x->c[i];
            for (int j=i-1; j<=x->n-2; ++j)
              x->key[j] = x->key[j+1];
            for (int j=i; j<=x->n-1; ++j)
              x->c[j] = x->c[j+1];
            --x->n;
            disk_write(x);
            // delete c[i]
            delete x->c[i];
            // recursive
            _del(x->c[i-1], key);
          }
          else
          {
            // change c[i]
            x->c[i]->n = 2*t-1;
            x->c[i]->key[t-1] = x->key[i];
            for (int j=0; j<t-1; ++j)
              x->c[i]->key[j+t] = x->c[i+1]->key[j];
            if (!x->leaf)
            {
              for (int j=0; j<t; ++j)
                x->c[i]->c[j+t] = x->c[i+1]->c[j];
            }
            disk_write(x->c[i]);
            // change x
            auto *y = x->c[i+1];
            for (int j=i; j<=x->n-2; ++j)
              x->key[j] = x->key[j+1];
            for (int j=i+1; j<=x->n-1; ++j)
              x->c[j] = x->c[j+1];
            --x->n;
            disk_write(x);
            // delete c[i+1]
            delete y;
            // recursive
            _del(x->c[i], key);
          }
        }
      }
    }
  }
}

void BTree::del(char key)
{
  _del(root, key);
}

pair<Node*, int> BTree::_search(Node* x, char key)
{
  pair<Node*, int> pa;
  int i;
  for (i=0; i<x->n&&x->key[i]<key; ++i);
  if (i<x->n&&x->key[i]==key)
  {
    pa.first = x;
    pa.second = i;
  }
  else
  {
    if (!x->leaf)
      pa = _search(x->c[i], key);
    else
    {
      pa.first = NULL;
      pa.second = -1;
    }
  }
  return pa;
}

pair<Node*, int> BTree::search(char key)
{
  return _search(root, key);
}

char BTree::minimum(Node *node)
{
  auto *p = node;
  while (!p->leaf)
    p = p->c[0];
  return p->key[0];
}

char BTree::maximum(Node *node)
{
  auto *p = node;
  while (!p->leaf)
    p = p->c[p->n];
  return p->key[p->n-1];
}

void BTree::insert(char key)
{
  auto *p = root;
  if (p->n == 2*t - 1)
  {
    Node *node = new Node();
    node->n = 0;
    node->leaf = 0;
    node->c[0] = p;
    root = node;
    split_child(node, 0); 
    insert_nonefull(node, key);
  }
  else
    insert_nonefull(p, key);
}

void BTree::split_child(Node *x, int i)
{
  // create new child
  Node *y = new Node();
  y->n = t-1;
  y->leaf = x->c[i]->leaf;
  for (int j=0; j<t-1; ++j)
    y->key[j] = x->c[i]->key[t+j];
  if (!x->c[i]->leaf)
  {
    for (int j=0; j<=t-1; ++j)
      y->c[j] = x->c[i]->c[t+j];
  } 
  // change x
  for (int j=x->n-1; j>=i; --j)
    x->key[j+1] = x->key[j];
  x->key[i] = x->c[i]->key[t-1];
  for (int j=x->n; j>=i+1; --j)
    x->c[j+1] = x->c[j];
  x->c[i+1] = y;
  ++x->n;
  // change x->c[i]
  x->c[i]->n = t-1;
  disk_write(x);
  disk_write(y);
  disk_write(x->c[i]);
}

void BTree::insert_nonefull(Node *x, char key)
{
  if (x->leaf)
  {
    int i;
    for (i=x->n-1; i>=0&&x->key[i]>=key; --i)
      x->key[i+1] = x->key[i];
    ++i;
    x->key[i] = key;
    ++x->n;
    disk_write(x);
  }
  else
  {
    int i;
    for (i=x->n-1; i>=0&&x->key[i]>=key;--i);
    ++i;
    disk_read(x->c[i]);
    if (x->c[i]->n == 2*t-1)
    {
      split_child(x, i);
      if (key > x->key[i])
        ++i;
    }
    insert_nonefull(x->c[i], key);
  }
}

void BTree::print()
{
  queue<Node*> q;
  q.push(root);
  Node *p;
  while (!q.empty())
  {
    p = q.front();
    q.pop();
    disk_read(p);
    cout << "n="<<p->n<<", leaf="<<p->leaf<<endl;
    cout << "key= ";
    for (int i=0; i<p->n; ++i)
      cout << p->key[i]<<' ';
    cout << endl;
    if (!p->leaf)
      for (int i=0; i<=p->n; ++i)
        q.push(p->c[i]);
  }
}

int main()
{
  BTree t;
  t.insert('F'); 
  t.insert('S');
  t.insert('Q');
  t.insert('K');
  t.insert('C');
  t.insert('L');
  t.insert('H');
  t.insert('T');
  t.insert('V');
  t.insert('W');
  t.insert('M');
  t.insert('R');
  t.insert('N');
  t.insert('P');
  t.insert('A');
  t.insert('B');
  t.insert('X');
  t.insert('Y');
  t.insert('D');
  t.insert('Z');
  t.insert('E');
  //t.print();
  //cout << "minimum="<<t.minimum(t.get_root())<<endl;
  //cout << "maximum="<<t.maximum(t.get_root())<<endl;
  //auto pa = t.search('E');
  //cout << "search E="<<pa.first->key[pa.second]<<endl;
  //pa = t.search('G');
  //cout << "search G="<<pa.first << ' '<<pa.second<<endl;
  //// condition 1, when 'Y' in leaf node
  //t.del('Y');
  //cout << "after del Y"<<endl;
  //t.print();
  // condition 2, when 'K' in root
  //t.del('K');
  //cout << "after del K"<<endl;
  //t.print();
  // condition 3, when 'Q' in root
  //t.del('Q');
  //cout << "after del Q"<<endl;
  //t.print();
  // condition 4
  t.del('A');
  t.del('B');
  t.del('C');
  //t.del('F');
  t.del('M');
  t.print();
  
}
