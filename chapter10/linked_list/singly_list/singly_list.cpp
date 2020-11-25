#include <iostream>
#include "singly_list.h"
using namespace std;

SinglyList::~SinglyList()
{
  while (head!=NULL)
  {
    del(head->val);
  }
}

void SinglyList::insert(double x)
{
  SinglyNode *node = new SinglyNode(x);
  node->next = head;
  head = node;
  if (tail == NULL)
    tail = node;
}

SinglyNode *SinglyList::search(double key) const
{
  SinglyNode *p = head;
  while (p!=NULL && p->val != key)
  {
    p = p->next;
  }
  return p;
}

void SinglyList::del(double key)
{
  if (head == NULL)
    return;
  if (head->val == key)
  {
    auto *p = head;
    head = head->next;
    if (tail == p)
      tail == head;
    delete p;
    return;
  }
  auto *p = head;
  while (p->next!=NULL && p->next->val!=key)
    p = p->next;
  if (p->next!=NULL)
  {
    auto *q = p->next;
    p->next = q->next;
    if (q->next == NULL)
      tail = p;
    delete q;
  }
}

void SinglyList::print() const
{
  auto *p = head;
  while (p!=NULL)
  {
    cout << p->val<<' ';
    p = p->next;
  }
  cout << endl;
}

SinglyNode *SinglyList::get_tail()
{
  return tail;
}


///int main()
///{
///  SinglyList l;
///  l.insert(1);
///  l.insert(2);
///  l.insert(3);
///  l.insert(4);
///  l.print();
///  auto *p = l.search(2);
///  cout << "p->val="<<p->val<<endl;
///  p = l.search(3);
///  cout << "p is NULL="<<(p==NULL)<<endl;
///  l.print();
///  l.del(4);
///  l.print();
///  l.del(5);
///  l.print();
///  l.del(2);
///  l.print();
///  l.del(1);
///  l.print();
///}




















