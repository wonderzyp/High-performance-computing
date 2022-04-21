#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <benchmark/benchmark.h>
#include <tbb/parallel_invoke.h>

template <class T>
void quick_sort_parallel(T* data, size_t size){
  if (size<1) return;
  
  // 小粒度使用串行处理，减少调度开销
  if (size< (1<<16)) {
    std::sort(data, data+size, std::less<T>{});
    return;
  }

  size_t mid = std::hash<size_t>{}(size);
  mid ^= std::hash<void *>{}(static_cast<void *>(data));
  mid %= size;

  std::swap(data[0], data[mid]);
  T pivot = data[0];
  
  size_t left=0, right = size - 1;
  while(left < right){
    while(left < right && !(data[right] < pivot)) 
      --right;
    if (left < right) 
      data[left++] = data[right];
    while(left < right && data[left] < pivot) 
      ++left;
    if (left < right) 
      data[right--] = data[left]; 
  }

  data[left] = pivot;
  tbb::parallel_invoke([&] {
    quick_sort_parallel(data, left);
  }, [&]{
    quick_sort_parallel(data+left+1, size-left-1);
  });
}

size_t n=1<<24;

void BM_qs_STL(benchmark::State &bm){
  std::vector<int> arr(n);
  std::generate(arr.begin(), arr.end(), std::rand);
  for(auto _:bm){
    std::sort(arr.begin(), arr.end());
  }
}
BENCHMARK(BM_qs_STL);

void BM_qs_parallel(benchmark::State &bm){
  std::vector<int> arr(n);
  std::generate(arr.begin(), arr.end(), std::rand);
  for(auto _:bm){
    quick_sort_parallel(arr.data(), arr.size());
  }
}
BENCHMARK(BM_qs_parallel);


BENCHMARK_MAIN();