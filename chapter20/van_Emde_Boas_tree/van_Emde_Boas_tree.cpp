#include <iostream>
#include <math.h>
using namespace std;

const int INF = 10000000;

struct vEBTree
{
  vEBTree(int n);
  void print();
  void print(vEBTree*);
  int high(int x){return x/u_down;}
  int low(int x){return x%u_down;}
  int index(int x, int y){return x*u_down + y;}
  int u;
  int u_up;
  int u_down;
  int min;
  int max;
  vEBTree* summary;
  vEBTree* *clusters;
};

int minimum(vEBTree *v){return v->min;}
int maximum(vEBTree *v){return v->max;}
void insert(vEBTree *v, int n);
bool member(vEBTree *v, int x);
int preprocessor(vEBTree *v, int x);
int successor(vEBTree *v, int x);
void del(vEBTree *v, int x);

vEBTree::vEBTree(int n)
{
  min = max = INF;
  if (n == 2)
  {
    u = 2;
    summary = NULL;
    clusters = NULL;
    return;
  }
  int log_n = log(n)/log(2);
  u = pow(2, log_n);
  if (log_n % 2 == 0)
    u_up = u_down = pow(2, log_n / 2);
  else
  {
    u_up = pow(2, log_n/2+1);
    u_down = pow(2, log_n/2);
  }
  summary = new vEBTree(u_up);
  clusters = new vEBTree*[u_up];
  for (int i=0; i<u_up; ++i)
    clusters[i] = new vEBTree(u_down);
}

void vEBTree::print()
{
  print(this);
}

void vEBTree::print(vEBTree* v)
{
  if (v->u == 2)
    cout << "u=2 min="<<v->min<<" max="<<v->max<<endl;
  else
  {
    cout << "u="<<v->u_up*v->u_down<<" min="<<v->min<<" max="<<v->max<<endl;
    cout << " summary:"<<endl;
    print(v->summary);
    for (int i=0; i<v->u_up; ++i)
    {
      cout << " clusters["<<i<<"]:"<<endl;
      print(v->clusters[i]);
    }
  }
}


void insert(vEBTree *v, int x)
{
  if (minimum(v) == INF)
  {
    v->min = v->max = x;
    return;
  }
  if (v->u == 2)
  {
    if (x == 0)
      v->min = x;
    if (x == 1)
      v->max = x;
    return;
  }
  if (x < v->min)
    swap(x, v->min);
  vEBTree *cluster = v->clusters[v->high(x)];
  if (minimum(cluster) == INF)
  {
    cluster->min = cluster->max = v->low(x);
    insert(v->summary, v->high(x));
  }
  else
  {
    insert(cluster, v->low(x)); 
  }
  if (x > v->max)
    v->max = x;
}

bool member(vEBTree *v, int x)
{
  if (v->min == INF) return false;
  if (x < v->min || x > v->max)
    return false;
  if (x == v->min || x == v->max)
    return true;
  else if (v->u == 2)
    return false;
  return member(v->clusters[v->high(x)], v->low(x));
}

int preprocessor(vEBTree *v, int x)
{
  if (v->min==INF || v->min!=INF && x<= v->min)
    return INF;
  if (x > v->max)
    return v->max; 
  if (v->u == 2)
  {
    if (v->min==0 && x==1) return 0;
    else return INF;
  }
  vEBTree *cluster = v->clusters[v->high(x)];
  if (cluster->min < v->low(x))
    return v->index(v->high(x), preprocessor(cluster, v->low(x)));
  int summary_pre = preprocessor(v->summary, v->high(x));
  if (summary_pre == INF)
    return v->min;
  int cluster_max = maximum(v->clusters[summary_pre]);
  return v->index(summary_pre, cluster_max);
}

int successor(vEBTree *v, int x)
{
  if (v->u == 2)
  {
    if (x==0 && v->max==1) return 1;
    else return INF;
  }
  if (v->min == INF) return INF;
  if (x < v->min) return v->min;
  if (x >= v->max) return INF;
  auto *cluster = v->clusters[v->high(x)];
  if (cluster->max!=INF && cluster->max>v->low(x))
    return v->index(v->high(x), successor(cluster, v->low(x)));
  int summary_succ = successor(v->summary, v->high(x));
  if (summary_succ == INF)
    return INF;
  int cluster_min = minimum(v->clusters[summary_succ]);
  return v->index(summary_succ, cluster_min);
}

void del(vEBTree *v, int x)
{
  if (v->u == 2 && v->min!=INF)
  {
    if (v->min == v->max && x == v->min)
      v->min = v->max = INF;
    else if (v->min != v->max)
    {
      if (x == v->min) v->min = v->max;
      else if (x == v->max) v->max = v->min;
    }
  }
  if (x < v->min || x > v->max)
    return;
  if (x == v->min && v->min == v->max)
  {
    v->min = v->max = INF;
    return;
  }
  if (x == v->min)
  {
    int summary_min = minimum(v->summary);
    int cluster_min = minimum(v->clusters[summary_min]);
    v->min = v->index(summary_min, cluster_min);
    x = v->min; 
  }
  del(v->clusters[v->high(x)], v->low(x));
  if (minimum(v->clusters[v->high(x)]) == INF)
  {
    del(v->summary, v->high(x));
    if (v->max == x)
    {
      int summary_max = maximum(v->summary);
      if (summary_max == INF)
      {
        v->max = v->min;
        return;
      }
      int cluster_max = maximum(v->clusters[summary_max]);
      v->max = v->index(summary_max, cluster_max);
    }
    return;
  }
  if (x == v->max)
  {
    int summary_max = maximum(v->summary);
    int cluster_max = maximum(v->clusters[summary_max]);
    v->max = v->index(summary_max, cluster_max);
  }
}

int main()
{
  vEBTree v(16);
  insert(&v, 2);
  insert(&v, 3);
  insert(&v, 4);
  insert(&v, 5);
  insert(&v, 7);
  insert(&v, 14);
  insert(&v, 15);
  v.print();
  cout << "member(7)="<<member(&v, 7)<<endl;
  cout << "member(9)="<<member(&v, 9)<<endl;
  cout << "preprocessor(15)="<<preprocessor(&v, 15)<<endl;
  cout << "preprocessor(14)="<<preprocessor(&v, 14)<<endl;
  cout << "preprocessor(13)="<<preprocessor(&v, 13)<<endl;
  cout << "preprocessor(9)="<<preprocessor(&v, 9)<<endl;
  cout << "preprocessor(7)="<<preprocessor(&v, 7)<<endl;
  cout << "preprocessor(2)="<<preprocessor(&v, 2)<<endl;
  cout << "successor(0)="<<successor(&v, 0)<<endl;
  cout << "successor(5)="<<successor(&v, 5)<<endl;
  cout << "successor(9)="<<successor(&v, 9)<<endl;
  cout << "successor(15)="<<successor(&v, 15)<<endl;
  //del(&v, 15);
  //cout << "after del 15"<<endl;
  //v.print();
  //del(&v, 2);
  //cout << "after del 2"<<endl;
  //v.print();
  del(&v, 7);
  cout << "after del 7"<<endl;
  v.print();
}
