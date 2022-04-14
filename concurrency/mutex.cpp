/**
* @brief 互斥量
* ****************************************************************************************/


#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <mutex>
using namespace std;

int main(){

/**
* @brief 通过互斥量避免数据竞争(data_race)
* vector不是多线程安全的容器(MT-safe)
* ****************************************************************************************/
#if 0
  vector<int> arr;
  mutex mtx;

  thread t1([&]{
    for (int i=0; i<1000; ++i){
      mtx.lock();
      arr.push_back(1);
      mtx.unlock();
    }
  });
  thread t2([&]{
  for (int i=0; i<1000; ++i){
    mtx.lock();
    arr.push_back(2);
    mtx.unlock();
  }
  });
  t1.join();
  t2.join();
#endif

/**
* @brief 借助RAII思想自动上锁解锁————std::lock_guard
* ****************************************************************************************/
#if 0
  vector<int> arr;
  mutex mtx;

  thread t1([&]{
    for (int i=0; i<1000; ++i){
      std::lock_guard<std::mutex> grd(mtx);
      arr.push_back(1);
    }
  });
  thread t2([&]{
  for (int i=0; i<1000; ++i){
    std::lock_guard<std::mutex> grd(mtx);
    arr.push_back(2);
  }
  });
  t1.join();
  t2.join();
#endif

/**
* @brief std::unique_lock更灵活地管理锁
* ****************************************************************************************/
#if 0
  vector<int> arr;
  mutex mtx;

  thread t1([&]{
    for (int i=0; i<1000; ++i){
      std::unique_lock<std::mutex> grd(mtx);
      arr.push_back(1);
    }
  });
  thread t2([&]{
  for (int i=0; i<1000; ++i){
    std::unique_lock<std::mutex> grd(mtx, std::defer_lock); //defer_lock在
    grd.lock();
    arr.push_back(2);
    grd.unlock();
  }
  });
  t1.join();
  t2.join();
#endif

}


