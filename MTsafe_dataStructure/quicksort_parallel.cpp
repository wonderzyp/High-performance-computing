#include <list>
#include <future>
#include <vector>
#include <stack>
// #include 

/**
* @brief 基于栈实现的并行快速排序算法
* ****************************************************************************************/

template <typename T>
struct sorter
{
  struct chunk_to_sort
  {
    std::list<T> data;
    std::promise<std::list<T> > promise;
  };

  thread_safe_stack<chunk_to_sort> chunks; // 2
  std::vector<std::thread> threads;

  unsigned const max_thread_count;

  std::atomic<bool> end_of_data;

  sorter():
    max_thread_count(std::thread::hardware_concurrency()-1);
    end_of_data(false) {};

  ~sorter(){
    end_of_data = true;
    for (auto& elem : threads){
      elem.join();
    }
  }

  
  
};

template <typename T>
std::list<T> parallel_quicksort(std::list<T> input)
{
  if (input.empty())
  {
    return input;
  }

  sorter<T> s;


}



