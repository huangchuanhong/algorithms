// page 134 10.2-2
#include <iostream>
#include "singly_list.h"
using namespace std;

class StackBySinglyList
{
public:
  void push(double x);
  double pop();
  bool is_empty() const;
  void print() const;
private:
  SinglyList l;
};

void StackBySinglyList::push(double x)
{
  l.insert(x);
}

double StackBySinglyList::pop()
{
  auto *p = l.get_head();
  if (p == NULL) 
    throw;
  double val = p->val;
  l.del(val);
  return val;
}

inline bool StackBySinglyList::is_empty() const
{
  return l.is_empty();
}

inline void StackBySinglyList::print() const
{
  l.print();
}


int main()
{
  StackBySinglyList s;
  s.push(1);
  s.push(2);
  s.push(3);
  s.print();
  cout << "pop "<<s.pop()<<endl;
  s.print();
  cout << "pop " << s.pop()<<endl;
  s.print();
  cout << "pop " << s.pop()<<endl;
  s.print();
  s.pop();
}
