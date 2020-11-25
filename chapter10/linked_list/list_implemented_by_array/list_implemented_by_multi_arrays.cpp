// page 134 10.3
#include <iostream>
using namespace std;

const int SIZE=6;
double KEYS[SIZE];
int PREVS[SIZE];
int NEXTS[SIZE];
int FREE = 0;

void INITLIZE()
{
  for (int i=0; i<SIZE; ++i)
  {
    PREVS[i] = i - 1;
    NEXTS[i] = i + 1;
  }
  NEXTS[SIZE-1] = -1;
}

int ALLOCATE_OBJECT()
{
  if (FREE == -1)
    throw;
  int cur = FREE;
  FREE = NEXTS[FREE];
  if (FREE != -1)
    PREVS[FREE] = -1;
  return cur;
}

void FREE_OBJECT(int id)
{
  NEXTS[id] = FREE;
  if (FREE != -1)
    PREVS[FREE] = id;
  PREVS[id] = -1;
  FREE = id;
}

int _search_next_invalid_pf(int pf, int n)
{
  while (pf != -1 && pf >= n)
    pf = NEXTS[pf];
  return pf;
}

int _search_next_invalid_pl(int pl, int n)
{
  while (pl != -1 && pl < n)
    pl = NEXTS[pl];
  return pl;
}

void _swap(int pf, int pl, int& head, int& free)
{
  int tmp_pf_prev = PREVS[pf];
  int tmp_pf_next = NEXTS[pf];
  double tmp_pf_key = KEYS[pf];
 
  PREVS[pf] = PREVS[pl];
  KEYS[pf] = KEYS[pl];
  NEXTS[pf] = NEXTS[pl];
  if (PREVS[pf] != -1)
    NEXTS[PREVS[pf]] = pf;
  else
    head = pf;
  if (NEXTS[pf] != -1)
    PREVS[NEXTS[pf]] = pf;
  
  PREVS[pl] = tmp_pf_prev;
  KEYS[pl] = tmp_pf_key;
  NEXTS[pl] = tmp_pf_next;
  if (PREVS[pl] != -1)
    NEXTS[PREVS[pl]] = pl;
  else
    free = pl;
  if (NEXTS[pl] != -1)
    PREVS[NEXTS[pl]] = pl;
}

void COMPACTIFY_LIST(int& head, int& free, int n)
{
  int pf = free;
  int pl = head;
  while (true)
  {
    pf = _search_next_invalid_pf(pf, n);
    if (pf == -1)
      return;
    int pf_next = NEXTS[pf];
    pl = _search_next_invalid_pl(pl, n);
    if (pl == -1)
      return;
    int pl_next = NEXTS[pl];
    _swap(pf, pl, head, free);
    pf = pf_next;
    pl = pl_next;
  }
}

void PRINT()
{
  cout << "PREVS="<<endl;
  for (int i=0; i<SIZE; ++i)
    cout << PREVS[i]<<' ';
  cout << endl;

  cout << "KEYS="<<endl;
  for (int i=0; i<SIZE; ++i)
    cout << KEYS[i]<<' ';
  cout << endl;

  cout << "NEXTS="<<endl;
  for (int i=0; i<SIZE; ++i)
    cout << NEXTS[i]<<' ';
  cout << endl;
}

class DoublyList
{
public:
  DoublyList():head(-1){}
  void insert(double key);
  int search(double key);
  int del(double key);
  void print() const;
  bool is_empty() const;
  int &get_head(){return head;}
private:
  int head;
};

void DoublyList::insert(double key)
{
  int curr = ALLOCATE_OBJECT();
  NEXTS[curr] = head;
  KEYS[curr] = key;
  PREVS[curr] = -1;
  PREVS[head] = curr;
  head = curr;
}

int DoublyList::search(double key)
{
  int cur = head;
  while (cur != -1 && KEYS[cur] != key)
    cur = NEXTS[cur];
  return cur;
}

int DoublyList::del(double key)
{
  int cur = search(key);
  if (cur != -1)
  {
    if (PREVS[cur] == -1)
      head = NEXTS[cur];
    else
      NEXTS[PREVS[cur]] = NEXTS[cur];
    if (NEXTS[cur] != -1)
      PREVS[NEXTS[cur]] = PREVS[cur];
    FREE_OBJECT(cur);
  }
}

void DoublyList::print() const
{
  int p = head;
  while (p!=-1)
  {
    cout << KEYS[p] << ' ';
    p = NEXTS[p];
  }
  cout << endl;
}

inline bool DoublyList::is_empty() const
{
  if (head == -1)
    return true;
  else return false;
}

int main()
{
  INITLIZE();
  PRINT();
  DoublyList l1, l2;
  l1.insert(1);
  cout << "l1 after insert 1"<<endl;
  PRINT();
  l1.insert(2);
  cout << "l1 after insert 2"<<endl;
  PRINT();
  l1.del(1);
  cout << "l1 after del 1" << endl;
  PRINT();
  l1.print();
  cout << "before compact, head="<<l1.get_head()<<", FREE="<<FREE<<endl;
  COMPACTIFY_LIST(l1.get_head(), FREE, 1);
  cout << "after compact, head="<<l1.get_head()<<", FREE="<<FREE<<endl;
  cout << "l1 after compact"<<endl;
  PRINT();
  l1.print();
  l1.insert(1);
  cout << "l1 after insert 1"<<endl;
  PRINT();
  l1.print();
  l1.insert(3);
  cout << "l1 after insert 3"<<endl;
  PRINT();
  l1.insert(4);
  cout << "l1 after insert 4"<<endl;
  PRINT();
  cout << "l1="<<endl;
  l1.print();
  l2.insert(5);
  cout << "l2 after insert 5"<<endl;
  PRINT();
  l2.insert(6);
  cout << "l2 after insert 6"<<endl;
  PRINT();
  cout << "l2="<<endl;
  l2.print();
  l1.del(1);
  cout << "l1 after del 1"<<endl;
  PRINT();
  l1.print();
  l2.insert(7);
  cout << "l2 after insert 7"<<endl;
  PRINT();
  l2.print();
}


