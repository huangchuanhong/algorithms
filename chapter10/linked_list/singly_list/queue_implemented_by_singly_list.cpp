// page 134, 10.2-3
#include <iostream>
#include "singly_list.h"
using namespace std;

class QueueBySinglyList
{
public:
  ~QueueBySinglyList(){l.~SinglyList();}
  void enqueue(double x);
  double dequeue();
  bool is_empty() const{return l.is_empty();}
  void print() const{l.print();}
private:
  SinglyList l;
};


void QueueBySinglyList::enqueue(double x)
{
  l.insert(x);
}

double QueueBySinglyList::dequeue()
{
  auto *p = l.get_tail();
  if (p == NULL)
    throw;
  double x = p->val;
  l.del(x);
  return x;
}


int main()
{
  QueueBySinglyList q;
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);
  q.print();
  cout << "dequeue "<<q.dequeue()<<endl;
  q.print();
  cout << "dequeue "<<q.dequeue()<<endl;
  q.print();
  q.enqueue(4);
  q.print();
  cout << "dequeue "<<q.dequeue()<<endl;
  q.print();
}
