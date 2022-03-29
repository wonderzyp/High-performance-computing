#include <iostream>
#include <vector>
#include <thread>
#include <cmath>
using std::vector;


void myfun(){
  double i;
  for (i=0; i<6; ++i){
    i = i+1;
    i = std::sqrt(i);
  }
  printf("%0.6f ",i);
};

void parall_fun(vector<double>& data) {

  unsigned int const len = data.size();
  if (len==0) return;

  unsigned int const min_per_threads = 25; // 每个线程设置最低处理个数，避免造成浪费
  unsigned int const max_threads = (len + min_per_threads-1)/min_per_threads; // 这个公式应该省略了步骤，大致是取下界
  unsigned int const hardware_threads = std::thread::hardware_concurrency();

  unsigned int const num_threads = std::min( hardware_threads !=0 ? hardware_threads : 2, max_threads);

  unsigned int const block_size = len/num_threads;

  std::vector<std::thread> threads(num_threads-1); // 容器管理线程，启动线程数比num_threads少1，因为启动前已有一个主线程

  for (int i=0; i<num_threads-1; ++i){
    threads[i] = std::thread(myfun);
  }

  for (int i=0; i<num_threads-1; ++i){
    threads[i].join();
  }
}



int main()
{
  std::cout<< std::thread::hardware_concurrency()<< std::endl;
  std::vector<double> data(61,0);
  parall_fun(data);
  return 0;
}