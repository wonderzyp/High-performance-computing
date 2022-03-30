#include <mutex>
#include <thread>
#include <iostream>
#include <vector>
#include <chrono>

using std::vector;
using std::cout;
using std::endl;
using std::cin;

struct Box
{
  explicit Box(int num) : num_things(num) {}
  int num_things;
  std::mutex m;
};

void transfer(Box &from, Box& to, int num)
{
  // 此时均未实际取得锁------> std::defer_lock
  std::unique_lock<std::mutex> lock1(from.m, std::defer_lock);
  std::unique_lock<std::mutex> lock2(to.m, std::defer_lock);

  // std::unique_lock<std::mutex> lock1(from.m, std::adopt_lock);
  // std::unique_lock<std::mutex> lock2(to.m, std::adopt_lock);
  // lock1.lock();
  // lock2.lock();
  std::lock(lock1, lock2);

  from.num_things -=num;
  to.num_things += num;

  printf("from num_things: %d\n", from.num_things);
  printf("to num_things :%d\n", to.num_things);
}

int main()
{
  Box box1(100);
  Box box2(200);

  std::thread t1(transfer, std::ref(box1), std::ref(box2), 10);
  std::thread t2(transfer, std::ref(box2), std::ref(box1), 5);

  t1.join();
  t2.join();
}