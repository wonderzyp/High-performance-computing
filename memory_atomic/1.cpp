/**
* @brief 强制访问顺序借助std::atomic<bool>变量实现
* ****************************************************************************************/

#include <vector>
#include <atomic>
#include <iostream>
#include <thread>
#include <chrono>
#include <future>

std::vector<int> data;
std::atomic<bool> data_ready(false);

void reader_thread()
{
  // 当数据尚未准备好时，2s后再询问状态
  // 该循环保证了数据访问的顺序
  while(!data_ready.load())
  {
    std::this_thread::sleep_for(std::chrono::seconds(2));
  }
  std::cout<<"The answer="<<data[0]<<"\n";  // 2
}

void writer_thread()
{
  data.push_back(42);  // 3
  data_ready=true;  // 4
}

int main()
{
  std::thread t1(reader_thread);
  std::thread t2(writer_thread);

  t1.join();
  t2.join();
}