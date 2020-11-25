#include <iostream>
#include "queue.h"
using namespace std;

class StackWith2Queue
{
public:
  StackWith2Queue(int max_size_);
  ~StackWith2Queue(){delete q1; delete q2;}
  void push(double x);
  double pop();
  bool is_empty() const;
  bool is_full() const;
private:
  Queue *q1;
  Queue *q2;
  Queue *push_q;
  Queue *pop_q;
  int max_size;
};

StackWith2Queue::StackWith2Queue(int max_size_)
{
  max_size = max_size_;
  q1 = new Queue(max_size);
  q2 = new Queue(max_size);
  push_q = q1;
  pop_q = q2;
}

void StackWith2Queue::push(double x)
{
  if (is_full())
    throw;
  push_q->enqueue(x);
}

double StackWith2Queue::pop()
{
  if (is_empty())
    throw;
  double x = push_q->dequeue();
  while (!push_q->is_empty())
  {
    pop_q->enqueue(x);
    x = push_q->dequeue();
  }
  swap(push_q, pop_q);
  return x;
}

bool StackWith2Queue::is_empty() const
{
  if (push_q->is_empty())
    return true;
  return false;
}

bool StackWith2Queue::is_full() const
{
  if (push_q->is_full())
    return true;
  return false;
}

int main()
{
  StackWith2Queue s(4);
  s.push(1);
  s.push(2);
  cout << s.pop() << endl;
  s.push(3);
  cout << s.pop() << endl;
  cout << s.pop() << endl;
  s.push(4);
  s.push(5);
  s.push(6);
  s.push(7);
  s.push(8);
}
