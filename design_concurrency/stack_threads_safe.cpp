/**
* @brief 线程安全的栈
* ****************************************************************************************/

#include <exception>
#include <stack>
#include <future>
#include <thread>


struct empty_stack : std::exception
{
  const char* what() const throw();
};

template <typename T>
class threadsafe_stack
{
private:
  std::stack<T> data;
  mutable std::mutex m;
public:
  threadsafe_stack(){};
  threadsafe_stack(const threadsafe_stack& other) // 拷贝构造函数，访问前上锁
  {
    std::lock_guard<std::mutex> lock(other.m);
    data = other.data;
  }

  threadsafe_stack& operator= (const threadsafe_stack&) = delete; // 不允许赋值构造

  void push(T new_value)
  {
    std::lock_guard<std::mutex> lock(m);
    data.push(std::move(new_value));
  }

  std::shared_ptr<T> pop()
  {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) throw empty_stack();

    std::shared_ptr<T> const res(std::make_shared<T>(std::move(data.top())));

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




