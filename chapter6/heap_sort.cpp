#include <iostream>
#include <vector>
using namespace std;

class Heap
{
public:
  int heap_size;
  int length;
  vector<float> vec;
  Heap():heap_size(0), length(0){}
  Heap(vector<float> vec_):vec(vec_),heap_size(vec_.size()-1), length(vec_.size()-1){}
  int operator[](int i){return vec[i];}
  void swap_(int i, int j)
  {
    swap(vec[i], vec[j]);
  }
  void set_heap_size(int i)
  {
    heap_size = i;
  }
};

void max_heapity(Heap &A, int i)
{
  int l = 2*i;
  int r = 2*i + 1;
  int largest = i;
  if (l<=A.heap_size && A[l] > A[i])
    largest = l;
  if (r<=A.heap_size && A[r] > A[largest])
    largest = r;
  if (largest == i)
    return;
  A.swap_(i, largest);
  max_heapity(A, largest);
}

void build_max_heap(Heap &A)
{
  for (int i=A.heap_size/2; i>=1; --i)
  {
    max_heapity(A, i);
  }
}

void heap_sort(Heap &A)
{
  for (int i=A.heap_size; i>1; --i)
  {
    A.swap_(1, i);
    A.heap_size -= 1;
    max_heapity(A,1); 
  }
}

void heap_max(vector<double> &A)
{
  return A[1];
}


int main()
{
  Heap A({0, 5, 3, 17, 10, 84, 19, 6, 22, 9});
  for (int i=1; i<=A.heap_size; ++i)
      cout << A[i]<<' ';
  cout << endl;
  build_max_heap(A);
  for (int i=1; i<=A.heap_size; ++i)
  {
     cout<<A[i]<<' ';
  }
  cout << endl;
  heap_sort(A);
  for (int i=1; i<=A.length; ++i)
    cout << A[i]<<' ';
  cout << endl;
  A.set_heap_size(A.length);
  cout << "max="<<heap_max(A)<<endl;
  return 0;
}
