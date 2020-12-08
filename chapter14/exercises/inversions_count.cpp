// page 196, 14.1-7
#include <iostream>
#include <vector>
#include "order_statistic_tree.h"
using namespace std;

int inversions_count(const vector<int> &vec)
{
  Tree t;
  vector<int> a;
  int count = 0;
  for (int i=0; i<vec.size(); ++i)
  {
    Node *x = new Node(vec[i]);
    t.init_node(x);
    t.insert(x);
    a.push_back(t.rank(x));
  }
  for (int i=0; i<vec.size(); ++i)
  {
    // there are i-a[i]+1 items larger than vec[i] in {vec[0], ..., vec[i-1]}
    // there are t.rank(x)-a[i] items less than vec[i] in {vec[i+1], ..., vec[n-1]};
    // so totally t.rank(x)+i-2*a[i]+1 items that are inversions of x
    count += t.key_rank(vec[i]) + i - 2*a[i] + 1;
  }
  return count / 2;
}

int main()
{
  vector<int> vec{1,4,7,5,3,8,2};
  for (int i=0; i<vec.size(); ++i)
    cout << vec[i]<<' ';
  cout << endl;
  int count = inversions_count(vec);
  cout << "inversions_count="<<count <<endl;
}
