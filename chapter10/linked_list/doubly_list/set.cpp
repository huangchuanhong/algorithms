// page 134, 10.2-6
#include <iostream>
#include "list.h"
using namespace std;

class Set
{
public:
  Set();
  Set &Union(Set &u);
  void insert(double x);
  void release();
  void print();
private:
  DoublyListNode *nil;
};

Set::Set()
{
  nil = new DoublyListNode();
  nil->next = nil->prev = nil;
}

Set &Set::Union(Set &u)
{
  if (u.nil->next == u.nil)
  { 
    return *this;
  }
  auto *p = nil->prev;
  p->next = u.nil->next;
  u.nil->next->prev = p;
  p = u.nil->prev;
  nil->prev = p;
  p->next = nil;
  return *this;
}
void Set::insert(double x)
{
  DoublyListNode *p = new DoublyListNode(x);
  p->next = nil->next;
  nil->next->prev = p;
  nil->next = p;
  p->prev = nil;  
}

void Set::release()
{
  while (nil->next != nil)
  {
    auto *p = nil->next;
    nil->next = p->next;
    p->next->prev = nil;
    delete p;
  }
  delete nil;
}

void Set::print()
{
  auto *p = nil->next;
  while (p!=nil)
  {
    cout << p->val<<' ';
    p = p->next; 
  }
  cout << endl;
}

int main()
{
  Set s1, s2;
  s1.insert(1);
  s1.insert(2);
  s1.insert(3);
  s1.print();
  s2.insert(4);
  s2.insert(5);
  s2.insert(6);
  s2.print();
  Set &s3 = s1.Union(s2);
  s3.print();
  s3.release();
}
