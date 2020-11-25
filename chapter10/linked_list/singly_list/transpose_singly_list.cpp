#include <iostream>
#include "singly_list.h"

void transpose_singly_list(SinglyList &l)
{
  if (l.head == NULL)
    return;
  auto *p = l.head;
  if (p->next == NULL)
    return;
  auto *q = p->next;
  if (q->next == NULL)
  {
    q->next = p;
    p->next = NULL;
    l.head = q;
    return;
  }
  auto *r = q->next;
  while (r->next != NULL)
  {
    q->next = p;
    p = q;
    q = r;
    r = r->next;
  }
  q->next = p;
  r->next = q;
  l.head->next = NULL;
  l.head = r;
}


int main()
{
  SinglyList l;
  l.insert(1);
  l.insert(2);
  l.insert(3);
  l.print();
  transpose_singly_list(l);
  l.print();
}
