/**
* @brief async，接受带返回值的lambda，返回一个future
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
  cout<<"I know you click me"<<endl;
}

int main(){
  future<int> fret = std::async([&]{
    return download("hello.zip");
  });
  
  // 模拟下载途中鼠标点击
  std::this_thread::sleep_for(std::chrono::milliseconds(800));
  interact();
  int ret = fret.get();
  std::cout<<"Download result: "<<ret<<std::endl;
  return 0;
}