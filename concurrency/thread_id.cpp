#include <iostream>
#include <thread>
#include <vector>

using std::cout;
using std::endl;
using std::cin;

void fun()
{
  std::cout<<std::this_thread::get_id()<<std::endl;

}

int main()
{
  std::vector<std::thread> threads;
  for (unsigned int i=0; i<20; ++i){
    threads.push_back(std::thread(fun));
    cout<<"in main: "<<threads[i].get_id()<<endl;
  }

  for (auto& thread : threads){
    thread.join();
  }

  
}