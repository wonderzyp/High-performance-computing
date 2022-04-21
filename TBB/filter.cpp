/**
* @brief 筛选出大于0的元素
* ****************************************************************************************/
#include <iostream>
#include <tbb/parallel_for.h>
#include <tbb/concurrent_vector.h>
#include <vector>
#include <cmath>
#include <benchmark/benchmark.h>
using namespace std;

size_t n = 1<<27;
vector<float> a;
tbb::concurrent_vector<float> con_a;

/**
* @brief 串行版本
* ****************************************************************************************/
void func_original(){
  for (size_t i=0; i<n; ++i){
    float val = sin(i);
    if (val > 0)
      a.push_back(val);
  }
}


/**
* @brief 并行
* ****************************************************************************************/
void func_parallel(){
  tbb::parallel_for(tbb::blocked_range<size_t>(0,n),
  [&] (tbb::blocked_range<size_t> r) {
    std::vector<float> local_a;
    for (size_t i=r.begin(); i<r.end(); ++i){
      float val = sin(i);
      if (val > 0) local_a.push_back(val);
    }


    auto it = con_a.grow_by(local_a.size());
    for (size_t i=0; i<local_a.size(); ++i){
      *it++ = local_a[i];
    }
  });
}




// benchmark
void BM_original(benchmark::State &bm){
  for(auto _:bm){
    func_original();
  }
}
BENCHMARK(BM_original);

void BM_parallel(benchmark::State &bm){
  for(auto _:bm){
    func_parallel();
  }
}
BENCHMARK(BM_parallel);


BENCHMARK_MAIN();
