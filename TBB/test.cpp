#include <iostream>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>
#include <tbb/parallel_reduce.h>
#include <vector>
#include <cmath>
#include <benchmark/benchmark.h>

using namespace std;

constexpr size_t n = 1<<27;
std::vector<float> a(n);

void func(std::vector<float>& a){
  for (size_t i=0; i<a.size(); ++i){
    a[i] = sin(i);
  }
}

void BM_for(benchmark::State &bm){
  for (auto _:bm){
    func(a);
  }
}
BENCHMARK(BM_for);

void BM_reduce(benchmark::State &bm){
  for (auto _: bm){
    float res = 0;
    for (size_t i=0; i<a.size(); ++i){
      res += a[i];
    }
    benchmark::DoNotOptimize(res);
  }
}

BENCHMARK(BM_reduce);

BENCHMARK_MAIN();
