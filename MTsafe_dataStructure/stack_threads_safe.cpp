/**
* @brief 线程安全的栈
* ****************************************************************************************/

#include <exception>
#include <stack>
#include <future>
#include <thread>
#include <mutex>


struct empty_stack : std::exception
{
  const char* what() const throw();
};

template <typename T>
class threadsafe_stack
{
private:
  std::stack<T> data;
  mutable std::mutex m; // 互斥量m保证基本的线程安全，同一时刻仅一个线程可访问到数据
public:
  threadsafe_stack(){};
  threadsafe_stack(const threadsafe_stack& other) // 拷贝构造函数，拷贝前上锁
  {
    // 使用互斥量保证复制结构的正确性，此方式优于成员初始化列表
    std::lock_guard<std::mutex> lock(other.m);
    data = other.data;
  }

  threadsafe_stack& operator= (const threadsafe_stack&) = delete; //拷贝一个互斥量没有意义

  void push(T new_value)
  {
    std::lock_guard<std::mutex> lock(m);
    data.push(std::move(new_value));
  }

  std::shared_ptr<T> pop()  // shared_ptr避免内存管理
  {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) throw empty_stack(); // pop 前检查是否为空

    // 创建res可能会抛出异常
    // 1. 没有足够的内存调用make_shared
    // 2. 拷贝或移动到新分配的内存中返回时抛出异常
    std::shared_ptr<T> const res(std::make_shared<T>(std::move(data.top()))); // 修改堆栈前，分配返回值

    data.pop();
    return res;
  }

  void pop(T& value)
  {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) throw empty_stack();

    value=std::move(data.top());
    data.pop();
  }

  bool empty() const
  {
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
  }
};

// 将top和pop融合了，避免竞争，通过shared_ptr防止丢失top值




