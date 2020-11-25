#include <iostream>
#include "singly_list.h"
using namespace std;

class SentineledSinglyList
{
public:
  SentineledSinglyList():nil(new SinglyNode()){}
  ~SentineledSinglyList();
  void insert(double x);
  SinglyNode *search(double key);
  void del(SinglyNode *node);
  bool is_empty() const{if (nil->next !=NULL) return true; else return false;}
  void print() const;
private:
  SinglyNode *nil;
};

void SentineledSinglyList::insert(double x)
{
  SinglyNode *p = new SinglyNode(x);
  p->next = nil->next;
  nil->next = p;
}

SinglyNode *SentineledSinglyList::search(double key)
{
  auto *p = nil->next;
  while (p != NULL && p->val != key)
    p = p->next;
  return p;
}

void SentineledSinglyList::del(SinglyNode *node)
{
  auto *p = nil;
  while (p->next != NULL && p->next->val != node->val)
    p = p->next;
  if (p->next != NULL)
  {
    auto *q = p->next;
    p->next = q->next;
    delete q;
  }
}

void SentineledSinglyList::print() const
{
  auto *p = nil->next;
  while (p!=NULL)
  {
    cout << p->val << ' ';
    p = p->next;
  }
  cout << endl;
}

SentineledSinglyList::~SentineledSinglyList()
{
   while (nil->next != NULL)
   {
     auto *node = nil->next;
     del(node); 
   }
   delete nil;
}

int main()
{
  SentineledSinglyList l;
  l.insert(1);
  l.insert(2);
  l.insert(3);
  l.insert(4);
  l.print();
  auto *p = l.search(2);
  l.del(p);
  l.print();
  p = l.search(4);
  l.del(p);
  l.print();
  p = l.search(1);
  l.del(p);
  l.print();
}
