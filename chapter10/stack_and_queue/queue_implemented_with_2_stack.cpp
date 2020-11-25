// page 131 10.1-6
#include <iostream>
#include "stack.h"
using namespace std;

class QueueWith2Stack
{
public:
  QueueWith2Stack(int max_size_);
  ~QueueWith2Stack(){delete stack_in_p; delete stack_out_p;}
  void enqueue(double x);
  double dequeue();
  bool is_empty() const;
  bool is_full() const;
private:
  int max_size;
  Stack *stack_in_p;
  Stack *stack_out_p;
};

inline bool QueueWith2Stack::is_full() const
{
  if (stack_in_p->is_full())
    return true;
}

inline bool QueueWith2Stack::is_empty() const
{
  if (stack_out_p->is_empty())
  {
    while(!stack_in_p->is_empty())
      stack_out_p->push(stack_in_p->pop());
  }
  return stack_out_p->is_empty();
}

inline QueueWith2Stack::QueueWith2Stack(int max_size_)
{
  max_size = max_size_;
  stack_in_p = new Stack(max_size);
  stack_out_p = new Stack(max_size);
}

void QueueWith2Stack::enqueue(double x)
{
  if (is_full())
    throw;
  stack_in_p->push(x);
}

double QueueWith2Stack::dequeue()
{
  if (is_empty())
    throw;
  return stack_out_p->pop();
}

int main()
{
  QueueWith2Stack q(4);
  q.enqueue(1);
  q.enqueue(2);
  cout << q.dequeue()<<endl;
  q.enqueue(3);
  cout << q.dequeue()<<endl;
  q.enqueue(4);
  q.enqueue(5);
  q.enqueue(6);
  cout << q.dequeue() <<endl;
  cout << q.dequeue() << endl;
  q.enqueue(7);
  q.enqueue(8);
  q.enqueue(9);
  q.enqueue(10);
  q.enqueue(11);
}
