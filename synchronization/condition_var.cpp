/**
* @brief 线程1创建并初始化vector，线程2将线程1创建vector中所有元素*2

* ****************************************************************************************/

#include <mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <condition_variable>

using std::vector;
using std::cout;
using std::endl;
using std::cin;

std::mutex mut;
std::vector<int> data_vec;
std::condition_variable data_cond;


void prepar_vector(){
  std::lock_guard<std::mutex> lk(mut); //对数据上锁
  for (int i=0; i<500; ++i){
    data_vec.push_back(i);
  }
  data_cond.notify_one(); // 通知所有的等待线程
}

void process_vector(){
  std::unique_lock<std::mutex> lk(mut);
  data_cond.wait( lk, []{return !data_vec.empty();} );
  for (auto& elem : data_vec){
    elem = elem*2;
    printf("%d ", elem);
  }

  lk.unlock();
}

int main()
{
  std::thread t_pre(prepar_vector);
  std::thread t_process(process_vector);

  t_pre.join();
  t_process.join();
}


