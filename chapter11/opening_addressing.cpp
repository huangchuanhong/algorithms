#include <iostream>
using namespace std;

struct Data
{
  Data(int k, double v):key(k),val(v){}
  int key;
  double val;
};

class HashTable
{
public:
  HashTable(int m_);
  virtual ~HashTable();
  void insert(Data *data);
  Data *search(int key) const;
  void del(Data *data);
  void print() const;
protected:
  int m;
  Data* *table;
  bool *flags;
  virtual int hash_func(int key) const=0;
};

class LinearProbingHashTable: public HashTable
{
public:
  LinearProbingHashTable(int m_):HashTable(m_){}
private:
  int hash_func(int key) const override;
};

class QuatraticProbingHashTable: public HashTable
{
public:
  QuatraticProbingHashTable(int m_, int c1_, int c2_):HashTable(m_),c1(c1_),c2(c2_){}
private:
  int hash_func(int key) const override;
  int c1, c2;
};

class DoubleHashTable: public HashTable
{
public:
  DoubleHashTable(int m_):HashTable(m_){}
private:
  int hash_func(int key) const override;
};

HashTable::HashTable(int m_)
{
  m = m_;
  table = new Data*[m];
  flags = new bool[m];
  for (int i=0; i<10; ++i)
    flags[i] = false;
}

HashTable::~HashTable()
{
  if (table == NULL)
    return;
  for (int i=0; i<m; ++i)
  {
    if (table[i] != NULL)
      delete table[i];
  }
  delete[] table;
  delete[] flags;
}

void HashTable::insert(Data *data)
{
  int i = hash_func(data->key);
  if (table[i] == NULL)
    table[i] = data;
}


Data *HashTable::search(int key) const
{
  int i = hash_func(key);
  return table[i];
}

void HashTable::del(Data *data)
{
  if (data==NULL)
    return;
  int i = hash_func(data->key);
  if (table[i] == NULL)
    return;
  flags[i] = true;
  delete data;
  table[i] = NULL;
}

void HashTable::print() const
{
  for (int i=0; i<m; ++i)
  {
    cout << i << ": ";
    if (table[i] != NULL)
      cout << "key=" << table[i]->key << ",val="<<table[i]->val << endl;
    else
      cout << endl;
  }
}

int LinearProbingHashTable::hash_func(int key) const
{
  int i = key % m;
  int j;
  for (j=0; j<m; ++j)
  {
    if (table[i] != NULL && table[i]->key == key)
      return i;
    if (table[i] == NULL && flags[i] == false)
      return i;
    i = (i + 1) % m;
  }
  if (j==m)
  {
    cout << "table is full"<<endl;
    throw;
  }
}

int QuatraticProbingHashTable::hash_func(int key) const
{
  int h = key % m;
  int j, i=h;
  for (j=0; j<m; ++j)
  {
    if (table[i] != NULL && table[i]->key == key)
      return i;
    if (table[i] == NULL && flags[i] == false)
      return i;
    i = (h + j*c1 + j*j*c2) % m;
  }
  if (j == m)
  {
    cout << "table is full"<<endl;
    throw;
  }
}

int DoubleHashTable::hash_func(int key) const
{
  int h1 = key % m;
  int h2 = 1 + key %(m-1);
  int j=0, i=h1;
  for (j=0; j<m; ++j)
  {
    if (table[i] != NULL && table[i]->key == key)
      return i;
    if (table[i] == NULL && flags[i] == false)
      return i;
    i = (h1 + j*h2) % m;
  }
  if (j == m)
  {
    cout << "table is full"<<endl;
    throw;
  }
}

int main()
{
  //LinearProbingHashTable t(5);
  //QuatraticProbingHashTable t(11, 1, 3);
  DoubleHashTable t(11);
  t.insert(new Data(1, 1));
  t.insert(new Data(2, 2));
  t.insert(new Data(12, 12));
  t.print();
  auto *d = t.search(1);
  cout << "after delete Data(1, 1)"<<endl;
  t.del(d);
  t.print();
  t.insert(new Data(1, 1));
  cout << "after insert Data(1,1)"<<endl;
  t.print();
  t.insert(new Data(1, 1));
  cout << "after insert Data(1,1)"<<endl;
  t.print();
  t.insert(new Data(5, 5));
  cout << "after insert Data(5, 5)"<<endl;
  t.print();
  t.insert(new Data(5, 5));
  cout << "after insert Data(5, 5)"<<endl;
  t.print();
  t.insert(new Data(3, 3));
  cout << "after insert Data(3, 3)"<<endl;
  t.print();

}

