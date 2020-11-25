#include <iostream>
using namespace std;

class Queue
{
public:
  Queue():head(0),tail(0),max_size(256),a(new double[256+1]){}
  Queue(int max_size_):head(0),tail(0),max_size(max_size_),a(new double[max_size_+1]){}
  ~Queue(){delete[] a;}
  void enqueue(double x);
  double dequeue();
  bool is_empty() const;
  bool is_full() const;
  void print() const;
private:
  int head;
  int tail;
  int max_size; 
  double *a;
};

inline bool Queue::is_empty() const
{
  if (head == tail)
    return true;
  return false;
}

inline bool Queue::is_full() const
{
  int tail_plus = (tail + 1) % (max_size + 1);
  if (tail_plus == head)
    return true;
  return false;
}

inline void Queue::print() const
{
  for (int i=0; i<max_size+1; ++i)
    cout << a[i] << ' ';
  cout << endl;
}

