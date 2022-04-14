/**
* @brief mutable 和 读写锁 std::shared_mutex
* ****************************************************************************************/
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <shared_mutex>

class MTVector{
  std::vector<int> m_arr;
  mutable std::shared_timed_mutex m_mtx;
public:
  void push_back(int val){
    m_mtx.lock();
    m_arr.push_back(val);
    m_mtx.unlock();
  }

  // size()是const，若想改变m_mtx，需声明为mutable
  // size()仅读操作，运行多线程共享
  size_t size() const{
    m_mtx.lock_shared();
    size_t ret = m_arr.size();
    m_mtx.unlock_shared();
    return ret;
  }
};