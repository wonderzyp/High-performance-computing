#include <vector>
#include <cmath>
#include <iostream>
#include <tbb/task_group.h>
#include <tbb/parallel_for.h>
using namespace std;

/**
* @brief 映射
* 串行映射算法：时间复杂度O(N), 空间复杂度O(N)
* c线程并行算法：时间复杂度O(N/C)，空间复杂度O(N)
* ****************************************************************************************/

void map(vector<float>& a, size_t n){
    for (size_t i=0; i<n; ++i){
    a[i] = sin(i);
  }
}

void map_parallel(vector<float>& a, size_t n){
  size_t maxt=4;
  tbb::task_group tg;

  for (size_t t=0; t<maxt; ++t){
    auto beg = t*n/maxt;
    auto end = std::min(n, (t+1)*n/maxt);
    tg.run([&, beg, end] {
      for (size_t i=beg; i<end; ++i){
        a[i] = std::sin(i);
      }
    });
  }
tg.wait();
}

/**
* @brief parallel_for已封装好
* ****************************************************************************************/
int main(){
  size_t n = 1<<26;
  vector<float> a(n);
  vector<float> a_parallel(n);
  // map(a,n);
  // map_parallel(a_parallel, n);
  tbb::parallel_for(tbb::blocked_range<size_t>(0,n),
  [&] (tbb::blocked_range<size_t> r){
    for (size_t i = r.begin(); i<r.end(); ++i){
      a[i] = std::sin(i);
    }
  });

  return 0;
}