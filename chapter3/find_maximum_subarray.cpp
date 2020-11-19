#include <iostream>
#include <vector>
#include <float.h>
#include <random>
#include <time.h>
using namespace std;

// O(n^2)
float find_maximum_subarray_vilence(int&low, int&high, const vector<double> &array)
{
  double max_sum = -DBL_MAX;
  for (int i=0; i<array.size(); ++i)
  {
    double accum_sum = 0;
    for (int j=i; j<array.size(); ++j)
    {
      accum_sum += array[j];
      if (accum_sum > max_sum)
      {
        low = i;
        high = j;
        max_sum = accum_sum;
      }
    }
  }
  return max_sum;
}

float find_maximum_crossing_subarray(int &low, int &high, int mid, int start, int end, const vector<double> &array)
{
  float max_left_sum = -DBL_MAX; 
  float left_sum = 0;
  for (int i=mid; i>=start; --i)
  {
    left_sum += array[i];
    if (left_sum > max_left_sum)
    {
      max_left_sum = left_sum;
      low = i;
    }
  }
  float max_right_sum = -DBL_MAX;
  float right_sum = 0;
  for (int i=mid + 1; i<=end; ++i)
  {
    right_sum += array[i];
    if (right_sum > max_right_sum)
    {
      max_right_sum = right_sum;
      high = i;
    }
  } 
  return max_left_sum + max_right_sum;
}

// O(n*log(n))
float find_maximum_subarray_divide_and_conquer(int& low, int &high, const vector<double> &array)
{
  if (low == high)
  {
    return array[low];
  }
  else
  {
    int mid = (low + high) / 2;
    int left_low=low, left_high=mid;
    float left_sum = find_maximum_subarray_divide_and_conquer(left_low, left_high, array);
    int right_low = mid + 1, right_high = high;
    float right_sum = find_maximum_subarray_divide_and_conquer(right_low, right_high, array);
    int mid_low=mid, mid_high=mid+1;
    float mid_sum = find_maximum_crossing_subarray(mid_low, mid_high, mid, low, high, array);
    if (left_sum >= right_sum && left_sum >= mid_sum)
    {
      low = left_low;
      high = left_high;
      return left_sum;
    }
    else if (right_sum >= left_sum && right_sum >= mid_sum)
    {
      low = right_low;
      high = right_high;
      return right_sum;
    }
    else
    {
      low = mid_low;
      high = mid_high;
      return mid_sum; 
    }
  }
} 

vector<double> random_real_vector(int n, double min, double max)
{
  vector<double> vec(n);
  static default_random_engine e;
  static uniform_real_distribution<double> u(min, max);
  for (int i=0; i<n; ++i)
    vec[i] = u(e);
  return vec; 
}

// O(n)
// 算法导论42页作业4.1-5
double find_maximum_subarray_linear(int &low, int &high, const vector<double> &array)
{
  vector<double> sum_vec(array.size() + 1);
  sum_vec[0] = 0;
  for (int i=1; i<sum_vec.size(); ++i)
    sum_vec[i] = sum_vec[i-1] + array[i-1];
  int low1 = 1;
  low = high = 0;
  double max_sum = sum_vec[low];
  for (int i=2; i<sum_vec.size(); ++i)
  {
    double sum = sum_vec[i] - sum_vec[low1 - 1];
    if (sum > max_sum)
    {
      low = low1;
      high = i; 
      max_sum = sum;
    }
    else if (sum < 0)
    {
      low1 = i+1;
    }
  }
  low -= 1; 
  high -= 1;
  return max_sum;
}


int main()
{
  int N = 10000;
  int iters = 100;
  vector<double> array = random_real_vector(N, -100, 100);
  //vector<double> array={13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};

  int low = 0, high = array.size() - 1;
  double max_sum;
  clock_t start, end;
  start = clock();
  for (int i=0; i< iters; ++i)
    max_sum = find_maximum_subarray_divide_and_conquer(low, high, array);
  end = clock();
  cout << "low="<<low<<", high="<<high<<", max_sum="<<max_sum<<endl;
  cout << "time used:" << double(end - start) / iters / CLOCKS_PER_SEC << endl; 
  
  low = 0;
  high = array.size() - 1;
  start = clock();
  for (int i=0; i<iters; ++i)
    max_sum = find_maximum_subarray_vilence(low, high, array);
  end = clock();
  cout << "low="<<low<<", high="<<high<<", max_sum="<<max_sum<<endl;
  cout << "time used:" << double(end - start) / iters / CLOCKS_PER_SEC << endl;
  
  start = clock();
  for (int i=0; i<iters; ++i)
    max_sum = find_maximum_subarray_linear(low, high, array);
  end = clock();
  cout << "low="<<low<<", high="<<high<<", max_sum="<<max_sum<<endl;
  cout << "time used:" << double(end - start) / iters / CLOCKS_PER_SEC << endl;
  
}
