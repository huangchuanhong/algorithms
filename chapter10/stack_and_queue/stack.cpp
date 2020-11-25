#include <iostream>
#include "stack.h"
using namespace std;

//class Stack
//{
//public:
//  Stack();
//  Stack(int max_size_);
//  void push(double x);
//  double pop();
//  bool is_empty() const{if (top == -1) return true; else return false;}
//  bool is_full() const{if (top == max_size -1) return true; else return false;}
//  void print() const;
//private:
//  int max_size;
//  int top;
//  double *a; 
//};

Stack::Stack()
{
  max_size = 256;
  a = new double[max_size];
  top = -1;
}

Stack::Stack(int max_size_)
{
  max_size = max_size_;
  a = new double[max_size];
  top = -1;
}

void Stack::push(double x)
{
  if (is_full())
  {
    double *b = new double[max_size*2];
    for (int i=0; i<max_size; ++i)
      b[i] = a[i];
    delete[] a;
    a = b;
    max_size *=2;
  }
  a[++top] = x;
}

double Stack::pop()
{
  if (is_empty())
    throw;
  return a[top--];
}

void Stack::print() const
{
  for (int i=0; i<=top; ++i)
    cout << a[i] << ' ';
  cout << endl;
}

//int main()
//{
//  Stack s(2);
//  s.push(1);
//  s.push(2);
//  s.push(3);
//  s.print();
//  cout << s.pop()<<endl;
//  cout << s.pop()<<endl;
//  cout << s.pop()<<endl;
//  cout << s.pop()<<endl;
//}
