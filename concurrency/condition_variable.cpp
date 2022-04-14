#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>


int main(){
  std::condition_variable cv;
  std::mutex mtx;
  bool ready = false;

  std::thread t1([&]{
    std::unique_lock lck(mtx);
    cv.wait(lck, [&]{return ready;});
    
    std::cout<<"t1 is awake"<<std::endl;
  });

  std::this_thread::sleep_for(std::chrono::milliseconds(700));
  std::cout<<"notifying..."<<std::endl;
  cv.notify_one();
  ready=true;
  std::cout<<"notifying..."<<std::endl;
  cv.notify_one();

  t1.join();
}



