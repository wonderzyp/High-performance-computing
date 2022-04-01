#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>
 
void accumulate(std::vector<int>::iterator first,
                std::vector<int>::iterator last,
                std::promise<int> accumulate_promise)
{
  int sum = std::accumulate(first, last, 0);
  accumulate_promise.set_value(sum);  // 提醒 future
}
 
void do_work(std::promise<void> barrier)
{
  std::this_thread::sleep_for(std::chrono::seconds(1));
  barrier.set_value();
}
 
int main()
{
  // 演示用 promise<int> 在线程间传递结果。
  std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };

  std::promise<int> accumulate_promise;
  
  std::future<int> accumulate_future = accumulate_promise.get_future();
  
  std::thread work_thread(accumulate, numbers.begin(), numbers.end(),
                          std::move(accumulate_promise));

  // future::get() 将等待直至该 future 拥有合法结果并取得它
  // 无需在 get() 前调用 wait()
  //accumulate_future.wait();  // 等待结果
  std::cout << "result=" << accumulate_future.get() << '\n';
  work_thread.join();  // wait for thread completion

  // 演示用 promise<void> 在线程间对状态发信号
  std::promise<void> barrier;
  std::future<void> barrier_future = barrier.get_future();
  std::thread new_work_thread(do_work, std::move(barrier));
  barrier_future.wait();
  new_work_thread.join();
}