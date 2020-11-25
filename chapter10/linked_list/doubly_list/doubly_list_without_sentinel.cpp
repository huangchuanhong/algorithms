#include <iostream>
#include "list.h"
using namespace std;

void NormalDoublyList::insert(double x)
{
  DoublyListNode *p = new DoublyListNode(x);
  p->next = head;
  if (head != NULL)
    p->next->prev = p;
  head = p;
  p->prev = NULL;
}

DoublyListNode *NormalDoublyList::search(double key)
{
  DoublyListNode *p = head;
  while (p != NULL && p->val != key)
  {
    p = p->next;
  }
  return p;
}

void NormalDoublyList::del(DoublyListNode *node)
{
  if (node == NULL)
    return;
  if (node->prev != NULL)
    node->prev->next = node->next;
  else
    head = node->next;
  if (node->next != NULL)
    node->next->prev = node->prev;
}

NormalDoublyList::~NormalDoublyList()
{
  while (head != NULL)
  {
    auto *p = head;
    head = p->next;
    delete p;
  }
}

void NormalDoublyList::print()
{
  auto *p = head;
  while (p != NULL)
  {
    cout << p->val << ' ';
    p = p->next;
  }
  cout <<endl;
}

int main()
{
  NormalDoublyList L;
  L.insert(1);
  L.insert(2);
  L.insert(3);
  L.print();
  auto *p = L.search(2);
  cout << p->val<<endl;
  L.del(p);
  L.print();
  delete p;
  p = L.search(1);
  L.del(p);
  L.print();
  p = L.search(4);
  cout << p<<endl;
  p = L.search(3);
  L.del(p);
  L.print();
}
