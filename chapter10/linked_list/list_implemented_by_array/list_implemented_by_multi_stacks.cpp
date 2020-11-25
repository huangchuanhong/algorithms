// page 136 10.3-4
#include <iostream>
#include <vector>
using namespace std;

class DoublyList;
vector<DoublyList *> LS;
void FREE_OBJECT(int id);

const int SIZE=6;
int PREVS[SIZE];
double KEYS[SIZE];
int NEXTS[SIZE];
int TOP=-1;


int ALLOCATE_OBJECT()
{
  ++TOP;
  return TOP;
}

class DoublyList
{
public:
  friend void FREE_OBJECT(int id);
  DoublyList():head(-1){}
  void insert(double x);
  int search(double x);
  void del(double x);
  void print() const;
private:
  int head;
};


void FREE_OBJECT(int id)
{
  PREVS[id] = PREVS[TOP];
  KEYS[id] = KEYS[TOP];
  NEXTS[id] = NEXTS[TOP];
  if (PREVS[id] != -1)
    NEXTS[PREVS[id]] = id;
  if (NEXTS[id] != -1)
    PREVS[NEXTS[id]] = id;  
  for (int i=0; i<LS.size(); ++i)
  {
    if (LS[i]->head == TOP)
    {
      LS[i]->head = id;
      break;
    } 
  }
  --TOP;
}

void PRINT()
{
  cout << "PREVS="<<endl;
  for (int i=0; i<=TOP; ++i)
    cout << PREVS[i]<<' ';
  cout << endl;

  cout << "KEYS="<<endl;
  for (int i=0; i<=TOP; ++i)
    cout << KEYS[i]<<' ';
  cout << endl;

  cout << "NEXTS="<<endl;
  for (int i=0; i<=TOP; ++i)
    cout << NEXTS[i]<<' ';
  cout << endl;
}

void DoublyList::insert(double x)
{
  int id = ALLOCATE_OBJECT();
  cout << "id="<<id << endl;
  cout << "head="<<head<<endl;
  NEXTS[id] = head;
  if (head != -1)
    PREVS[NEXTS[id]] = id;
  PREVS[id] = -1;
  KEYS[id] = x;
  head = id; 
}

int DoublyList::search(double x)
{
  int curr = head;
  while (curr != -1 && KEYS[curr] != x)
  {
    curr = NEXTS[curr];
  }
  return curr;
}

void DoublyList::del(double x)
{
  int curr = search(x);
  if (PREVS[curr] == -1)
    head = NEXTS[curr];
  else
    NEXTS[PREVS[curr]] = NEXTS[curr];
  if (NEXTS[curr] != -1)
    PREVS[NEXTS[curr]] = PREVS[curr];
  FREE_OBJECT(curr);
}

void DoublyList::print() const
{
  int curr = head;
  while (curr != -1)
  {
    cout << KEYS[curr]<<' ';
    curr = NEXTS[curr];
  }
  cout << endl;
}


int main()
{
  PRINT();
  DoublyList l1, l2;
  LS.push_back(&l1);
  LS.push_back(&l2); 
  l1.insert(1);
  cout << "l1 after insert 1"<<endl;
  PRINT();
  l1.insert(2);
  cout << "l1 after insert 2"<<endl;
  PRINT();
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



