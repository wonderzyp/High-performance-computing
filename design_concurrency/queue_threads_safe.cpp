/**
* @brief 线程安全的队列
 基于锁和条件变量
* ****************************************************************************************/

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class threadsafe_queue
{
private:
  std::mutex mut;
  std::queue<T> data_queue;
  std::condition_variable data_cond;

public:
  void push(T new_value)
  {
    std::lock_guard<std::mutex> lk(mut);
    
  }
}




