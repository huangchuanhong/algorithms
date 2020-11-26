#include <iostream>
using namespace std;

struct Data
{
  Data(int k, double v):key(k),val(v){}
  int key;
  double val;
};

struct Node
{
  Node(Data *d):data(d),prev(NULL),next(NULL){}
  Data *data;
  Node *prev;
  Node *next;
};

class HashTable
{
public:
  HashTable(int m_);
  void insert(Data *data);
  Node *search(int key) const;
  void del(Node *node);
  void print() const;
private:
  int m;
  Node* *table;
  int hash_func(int key) const;
};

HashTable::HashTable(int m_)
{
  m = m_;
  table = new Node*[m];
  for (int i=0; i<m; ++i)
    table[i] = NULL;
}

inline int HashTable::hash_func(int key) const
{
  return (key % m);
}

void HashTable::insert(Data *data)
{
  int i = hash_func(data->key);
  Node *p = new Node(data);
  p->next = table[i];
  if (table[i] != NULL)
    table[i]->prev = p;
  table[i] = p; 
}

Node *HashTable::search(int key) const
{
  int i = hash_func(key);
  auto *p = table[i];
  while (p!=NULL && p->data->key != key)
    p = p->next;
  return p;    
}

void HashTable::del(Node *node)
{
  int i = hash_func(node->data->key);
  if (node->prev != NULL)
    node->prev->next = node->next;
  else 
    table[i] = node->next;
  if (node->next != NULL)
    node->next->prev = node->prev;
  delete node;
}

void HashTable::print() const
{
  for (int i=0; i<m; ++i)
  {
    cout << i << ": ";
    auto *p = table[i];
    while (p!=NULL)
    {
      cout << "key:" << p->data->key << ", val:"<<p->data->val<<"->";
      p = p->next;
    }
    cout << endl;
  }
} 


int main()
{
  HashTable ht(5);
  ht.insert(new Data(1, 1));
  ht.insert(new Data(6, 6));
  ht.insert(new Data(3, 3));
  ht.insert(new Data(25, 25));
  ht.insert(new Data(11,11));
  ht.print();
  Node *p = ht.search(6);
  ht.del(p);
  cout << "after del 6"<<endl;
  ht.print();
  p = ht.search(1);
  ht.del(p);
  cout << "after del 1"<<endl;
  ht.print();
  p = ht.search(3);
  ht.del(p);
  cout << "after del 3"<<endl;
  ht.print();
}

