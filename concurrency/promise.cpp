/**
* @brief 不同于async自动分配线程，promise需手动分配线程
* 通过set_value()设置返回值
* ****************************************************************************************/

#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <future>
using namespace std;

int download(std::string file){
  for (int i=0; i<10; ++i){
    cout<<"Downloading "<<file
        <<"("<<i*10<<"%)..."<<endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
  }
  cout<<"Download complete: "<<file<<endl;
  return 404;
}

void interact(){
  std::this_thread::sleep_for(std::chrono::milliseconds(800));
  cout<<"I get your wink :) "<<endl;
}

int main(){
  std::promise<int> pret;
  std::thread t1([&]{
    auto ret = download("hello.zip");
    pret.set_value(ret);
  });
  std::future<int> fret = pret.get_future();
  interact();

  int ret = fret.get();
  cout<<"Download result: "<<ret<<endl;

  t1.join();
  return 0;
}