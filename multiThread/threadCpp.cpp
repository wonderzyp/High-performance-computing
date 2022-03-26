#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <future>


/**
* @brief 入门
* ****************************************************************************************/
// int main() {
//   std::thread t([](){
//   std::cout << "hello world." << std::endl;
//   });
//     std::cout<<t.get_id()<<std::endl;
//   t.join();
  
//   return 0;
// }
 

/**
* @brief 互斥量与临界区
如果在critical_section中不使用mutex，由于竞争的存在,输出结果可能不是23

// 例如: 两个线程t1,t2 同时想对当前变量cur=1执行+1操作
// 但t1和t2读取到的都是旧数据cur=1, 此时执行结束后, cur=2
// 理想态下,t2应读取被t1修改后的数据,最终的运算结果应为cur=3
// * ****************************************************************************************/
// int v=1;

// void critical_section(int change_v){
//   // 下面两个注释掉,可体会竞争的情况
//   static std::mutex mtx;
//   std::lock_guard<std::mutex> lock(mtx);

//   v += change_v; // 竞争操作
// }

// int main(){

//   for (int i=0; i<10000; ++i){
//   std::thread t1(critical_section, 2), t2(critical_section,3), t3(critical_section,1), t4(critical_section,10), t5(critical_section,6);
//   t4.join();
//   t3.join();
//   t5.join();
//   t1.join();
//   t2.join();
//   // std::cout<<v<<std::endl;
//   if (v!=23) std::cout<<"error occurs"<<std::endl;
//   v=1;
//   }

//   std::cout<<"finished"<<std::endl;
//   return 0;
// }



/**
* @brief std::unique_lock 可调用lock和unlock
* ****************************************************************************************/
// int v=1;

// void critical_section(int change_v){
//   static std::mutex mtx;
//   std::unique_lock<std::mutex> lock(mtx);

//   v = change_v;
//   std::cout<<v<<std::endl;
//   lock.unlock();

// // 如果在此处设置3s的休眠时间
// // 当线程t1休眠时,线程t2可获取lock锁,并输出3
//   std::this_thread::sleep_for(std::chrono::seconds(3));

//   lock.lock();
//   v+=1;
//   std::cout<<v<<std::endl;
// }

// // 不进行上锁
// // void critical_section(int change_v){

// //   v = change_v;
// //   std::cout<<v<<std::endl;

// //   v+=1;
// //   std::cout<<v<<std::endl;
// // }

// int main(){
//   std::thread t1(critical_section,1), t2(critical_section,3);

//   t1.join();
//   t2.join();

//   return 0;
// }


/**
* @brief std::future 特性
  获取异步任务的结果，可理解为一种线程同步手段
* ****************************************************************************************/
int main()
{
  // std::packaged_task 可用于封装任何可调用的目标, 进而实现异步调用
  // std::packaged_task 的模板参数为欲封装函数的类型
  std::packaged_task<int()> task([](){return 7;});

  std::future<int> result = task.get_future();
  std::thread(std::move(task)).detach();
  std::cout << "waiting...\n";

  result.wait(); //设置屏障，阻塞直到期物完成

  std::cout<<"finished!\n"<<"future result is "<<result.get()<<std::endl;
  return 0;
}






/**
* @brief
* ****************************************************************************************/

// void foo()
// {
//     // 模拟耗费大量资源的操作
//     std::this_thread::sleep_for(std::chrono::seconds(1));
// }
 
// void bar()
// {
//     // 模拟耗费大量资源的操作
//     std::this_thread::sleep_for(std::chrono::seconds(1));
// }
 
// int main()
// {
//     std::cout << "starting first helper...\n";
//     std::thread helper1(foo);
 
//     std::cout << "starting second helper...\n";
//     std::thread helper2(bar);
 
//     std::cout << "waiting for helpers to finish..." << std::endl;
//     helper1.join();
//     helper2.join();
 
//     std::cout << "done!\n";
// }