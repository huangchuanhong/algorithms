#include <iostream>
#include "queue.h"
using namespace std;

void Queue::enqueue(double x)
{
  if (is_full())
    throw;
  a[tail] = x;
  tail = (tail + 1) % (max_size + 1);
}

double Queue::dequeue()
{
  if (is_empty())
    throw;
  double x = a[head];
  head = (head + 1) % (max_size + 1);
  return x;
}

//int main()
//{
//  Queue q(4);
//  q.enqueue(1);
//  q.enqueue(2);
//  q.enqueue(3);
//  cout << "q.is_full="<<q.is_full()<<endl;
//  q.enqueue(4);
//  q.print();
//  cout << "q.is_full="<<q.is_full()<<endl;
//  cout << "dequeue="<< q.dequeue()<<endl;
//  cout << "q.is_full="<<q.is_full()<<endl;
//  cout << "q.is_empty="<<q.is_empty()<<endl;
//  cout << q.dequeue() <<endl;
//  cout << q.dequeue() << endl;
//  cout << q.dequeue() << endl;  
//  cout << "q.is_empty="<<q.is_empty()<<endl;
//  cout << q.dequeue() << endl;
//}
