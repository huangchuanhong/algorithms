//page 131, 10.1-5
#include <iostream>
using namespace std;

class Deque
{
public:
  Deque(int max_size_):head(0),tail(0),max_size(max_size_),a(new double[max_size_]){}
  ~Deque(){delete[] a;}
  void push_back(double x);
  void push_front(double x);
  double pop_back();
  double pop_front();
  bool is_empty() const{if (head==tail) return true; else return false;}
  bool is_full() const;
  void print()
  {
    for (int i=0; i<max_size; ++i)
      cout << a[i] <<' ';
    cout << endl;
  }
private:
  double *a;
  int tail;
  int head;
  int max_size;
};

bool Deque::is_full() const
{
  int new_tail = (tail + 1) % max_size;
  if (head == new_tail)
    return true;
  return false;
}

void Deque::push_back(double x)
{
  if (is_full())
    throw;
  a[tail] = x;
  tail = (tail + 1) % max_size;
}

void Deque::push_front(double x)
{
  if (is_full())
    throw;
  head = (head - 1) % max_size;
  a[head] = x;
}

double Deque::pop_back()
{
  if (is_empty())
    throw;
  tail = (tail - 1)%max_size;
  return a[tail];
}

double Deque::pop_front()
{
  if (is_empty())
    throw;
  double x = a[head];
  head = (head + 1) % max_size;
  return x;
}

int main()
{
  Deque dq(4);
  dq.push_back(1);
  dq.push_back(2);
  dq.push_back(3);
  cout << dq.pop_front()<<endl;
  cout << dq.pop_front() << endl;
  dq.push_back(4);
  dq.push_front(5);
  dq.print();
}
