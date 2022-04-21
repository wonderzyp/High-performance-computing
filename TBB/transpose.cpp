#include <iostream>
#include <tbb/blocked_range2d.h>
#include <tbb/parallel_for.h>
#include <vector>
#include <cmath>
#include <benchmark/benchmark.h>
using namespace std;


size_t n = 1<<14;

vector<float> a1(n*n);
vector<float> b1(n*n);

vector<float> a2(n*n);
vector<float> b2(n*n);

void auto_partitioner(){
  tbb::parallel_for(tbb::blocked_range2d<size_t>(0,n,0,n),
  [&](tbb::blocked_range2d<size_t> r) {
    for (size_t i=r.cols().begin(); i<r.cols().end(); ++i){
      for (size_t j=r.rows().begin(); j<r.rows().end(); ++j){
        b1[i*n+j] = a1[j*n+i];
      }
    }
  });
}

/**
* @brief simple_partitioner将矩阵分块，优化访存
* ****************************************************************************************/
void simple_partitioner(){
  size_t grain = 16;
  tbb::parallel_for(tbb::blocked_range2d<size_t>(0,n, grain,0,n, grain),
  [&](tbb::blocked_range2d<size_t> r) {
    for (size_t i=r.cols().begin(); i<r.cols().end(); ++i){
      for (size_t j=r.rows().begin(); j<r.rows().end(); ++j){
        b2[i*n+j] = a2[j*n+i];
      }
    }
  }, tbb::simple_partitioner{});
}



void BM_auto(benchmark::State &bm){
  for (auto _:bm){
    auto_partitioner();
  }
}
BENCHMARK(BM_auto);

void BM_simple(benchmark::State &bm){
  for (auto _:bm){
    simple_partitioner();
  }
}

BENCHMARK(BM_simple);

BENCHMARK_MAIN();