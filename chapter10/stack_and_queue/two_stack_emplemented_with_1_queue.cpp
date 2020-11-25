#include <iostream>
using namespace std;

class TwoStack
{
public:
  TwoStack(int max_size_);
  ~TwoStack(){delete[] a;}
  void push(double x, int idx);
  double pop(int idx);
  void print();
private:
  double *a;
  int top1, top2;
  int max_size;
  void push1(double x);
  void push2(double x);
  double pop1();
  double pop2();
};

inline TwoStack::TwoStack(int max_size_)
{
  max_size = max_size_;
  top1 = -1;
  top2 = max_size;
  a = new double[max_size];
}

void TwoStack::push1(double x)
{
  if (top1 + 1 == top2)
    throw;
  a[++top1] = x;
}

void TwoStack::push2(double x)
{
  if (top2 - 1 == top1)
    throw;
  a[--top2] = x;
}

void TwoStack::push(double x, int idx)
{
  if (idx == 1)
    push1(x);
  else
    push2(x);
}

double TwoStack::pop1()
{
  if (top1 == -1)
    throw;
  double x = a[top1--];
  return x;
}

double TwoStack::pop2()
{
  if (top2 == max_size)
    throw;
  double x = a[top2++];
  return x; 
}

double TwoStack::pop(int idx)
{
  if (idx == 1)
    return pop1();
  if (idx == 2)
    return pop2();
}

inline void TwoStack::print()
{
  for (int i=0; i<max_size; ++i)
    cout << a[i]<<' ';
  cout << endl;
}

int main()
{
  TwoStack ts(4);
  ts.push(1, 1);
  ts.push(2, 1);
  ts.push(3, 2);
  ts.push(4, 2);
  ts.print();
  double x = ts.pop(1);
  cout << x<<endl;
  x = ts.pop(2);
  cout << x<<endl;
  x = ts.pop(1);
  cout << x<<endl;
  x = ts.pop(2);
  cout << x<<endl;
  x = ts.pop(1);
}
