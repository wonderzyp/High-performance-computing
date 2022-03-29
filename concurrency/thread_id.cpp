#include <iostream>
#include <thread>
#include <vector>

using std::cout;
using std::endl;
using std::cin;

/**
* @brief 辨识线程
 std::this_thread::get_id()：返回当前运行的线程号
 .get_id()：对一个thread对象调用，返回该对象的线程号
* ****************************************************************************************/

void fun()
{
  std::cout<<std::this_thread::get_id()<<std::endl;

}

int main()
{
  std::vector<std::thread> threads;
  for (unsigned int i=0; i<3; ++i){
    threads.push_back(std::thread(fun));
    cout<<"in main: "<<threads[i].get_id()<<endl;
  }

  for (auto& thread : threads){
    thread.join();
  }


  // std::thread thread_noWork;
  // cout<<thread_noWork.get_id()<<endl;
  std::thread::id master_thread;


  if (std::this_thread::get_id() == master_thread){
    cout<<"yes "<<endl;
  }

  
}