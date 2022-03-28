#include <iostream>
#include <thread>

void hello()
{
  printf("\nhey boy!\n");
}

void hi()
{
  printf("\nhey girls!\n");
}


int main()
{
  std::thread thread_1(hello);

  std::thread thread_2 = std::move(thread_1); // 线程2负责原有线程1的任务，线程1与原先任务无关联

  thread_1=std::thread(hi);
  // thread_1 = std::move(thread_2);        // 不能对已关联任务的线程重复赋值

  thread_1.join();
  thread_2.join();
}
