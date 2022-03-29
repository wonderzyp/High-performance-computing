#include <mutex>
#include <thread>
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;
using std::cin;

/**
* @brief for循环对全局遍历进行10000次+1操作
  比较使用互斥量与不使用互斥量之间区别

  修改：一般将互斥量与其需要保护的数据放在同一类中，对其封装与保护
* ****************************************************************************************/

class ShareData
{
  int share_data_withLock = 1;
  std::mutex my_mutex;  // 上锁
public:
  void add_lock(){
  std::lock_guard<std::mutex> guard(my_mutex);
  ++share_data_withLock;
  }

  int getMem(){
    return share_data_withLock;
  }
};


int share_data_withoutLock = 1;

void add_withoutLock(){
  ++share_data_withoutLock;
}

int main()
{
  vector<std::thread> threads_withLock;
  vector<std::thread> threads_withoutLock;
  ShareData shareData;

  for (int i=0; i<10000; ++i){
    threads_withLock.push_back(std::thread(&ShareData::add_lock, &shareData));
  }

  for (int i=0; i<10000; ++i){
    threads_withoutLock.push_back(std::thread(add_withoutLock));
  }

  for (int i=0; i<10000; ++i){
    threads_withLock[i].join();
    threads_withoutLock[i].join();
  }

  cout<<"data with lock: "<<shareData.getMem()<<endl;
  cout<<"data without lock: "<<share_data_withoutLock<<endl;
}
