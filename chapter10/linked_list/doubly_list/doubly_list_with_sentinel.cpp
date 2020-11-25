#include <iostream>
#include "list.h"
using namespace std;

SentineledDoublyList::SentineledDoublyList()
{
  nil = new DoublyListNode();
  nil->next = nil;
  nil->prev = nil;
}

SentineledDoublyList::~SentineledDoublyList()
{
  while (nil->next != nil)
  {
    DoublyListNode *p = nil->next;
    nil->next = p->next;
    nil->next->prev = nil;
    delete p;
  } 
  delete nil;
}

void SentineledDoublyList::insert(double x)
{
  DoublyListNode *p = new DoublyListNode(x);
  p->next = nil->next;
  nil->next->prev = p; 
  nil->next = p;
  p->prev = nil;
}

DoublyListNode *SentineledDoublyList::search(double key)
{
  DoublyListNode *p = nil->next;
  while (p != nil && p->val != key)
  {
    p = p->next;
  }
  if (p ==  nil)
    return NULL;
  return p;
}

void SentineledDoublyList::del(DoublyListNode *node)
{
  node->prev->next = node->next;
  node->next->prev = node->prev;
}

void SentineledDoublyList::print()
{
  DoublyListNode *p = nil->next;
  while (p!=nil)
  {
    cout << p->val<<' ';
    p = p->next;
  }
  cout << endl;
}

int main()
{
  SentineledDoublyList l;
  l.insert(1);
  l.insert(2);
  l.insert(3);
  l.print();
  DoublyListNode *p = l.search(4);
  cout << "p is NULL="<<(p==NULL)<<endl;
  p = l.search(2);
  l.del(p);
  l.print();
  p = l.search(1);
  l.del(p);
  l.print();
  p = l.search(3);
  l.del(p);
  l.print();
}
