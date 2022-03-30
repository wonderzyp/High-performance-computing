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
  std::lock_guard<std::mutex> lk(mut);
  for (int i=0; i<500; ++i){
    data_vec.push_back(i);
  }
}

void process_vector(){
  std::unique_lock<std::mutex> lk(mut);
  data_cond.wait(
    lk, [] {return !data_vec.empty();}
  );
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


