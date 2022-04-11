/**
* @brief 线程安全的队列
 基于锁和条件变量
* ****************************************************************************************/

#include <queue>
#include <mutex>
#include <condition_variable>

namespace Coarse_Threadsafe_Queue{
template <typename T>
class threadsafe_queue
{
private:
  mutable std::mutex mut;
  //std::queue<T> data_queue;
  // 将shared_ptr初始化过程移至push中，而不是直接使用数据值
  std::queue<std::shared_ptr<T>> data_queue;
  std::condition_variable data_cond;

public:
  threadsafe_queue(){};

  void push(T new_value)
  {
    // 将shared_ptr的构造过程移入push函数中
    std::shared_ptr<T> data( std::make_shared<T>(std::move(new_value)));
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(data);
    data_cond.notify_one(); // 使用notify_all, 大量线程被唤醒后发现不符合要求，再次休眠
  }


  void wait_and_pop(T& value)
  {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this]{return !data_queue.empty();});
    value = std::move(*data_queue.front());
    data_queue.pop();
  }

  bool try_pop(T& value)
  {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty())
      return false;
    value = std::move(*data_queue.front());
    data_queue.pop();
    return true;
  }

  std::shared_ptr<T> wait_and_pop()
  {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this]{return ! data_queue.empty(); } );
    // std::shared_ptr<T> res(std::make_shared<T>(std::move(data_queue.front())));
    
    std::shared_ptr<T> res = data_queue.front();

    data_queue.pop();
    return res;
  }

  std::shared_ptr<T> try_pop()
  {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty())
      return std::shared_ptr<T>();
    
    // std::shared_ptr<T> res(std::make_shared<T>(std::move(data_queue.front())));
    
    std::shared_ptr<T> res = data_queue.front();
    
    data_queue.pop();
    return res;
  }

  bool empty() const
  {
    std::lock_guard<std::mutex> lk(mut);
    return data_queue.empty();
  }
};
} // namespace Coarse_Threadsafe_Queue


// 粗粒度锁对整个queue数据结构进行保护
// 若需要使用细粒度锁，需对queue内部数据结构进行分析
namespace Fine_Threadsafe_Queue{

template <typename T>
class queue
{
private:
  struct node
  {
    T data;
    std::unique_ptr<node> next;

    node(T data_) : data(std::move(data_)){};
  };

  std::unique_ptr<node> head;
  node* tail;

public:
  queue(){};
  queue(const queue& other) = delete;
  queue& operator=(const queue& other) = delete;

  std::shared_ptr<T> try_pop(){
    if (!head){
      return std::shared_ptr<T>();
    }

    std::shared_ptr<T> const res(std::make_shared<T>(std::move(head->data)));
    std::unique_ptr<node> const old_head = std::move(head);
    head = std::move(old_head->next);
    return res;
  }
};




};
