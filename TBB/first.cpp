#include <iostream>
#include <string>
#include <tbb/parallel_invoke.h>
#include <tbb/task_group.h>
#include <thread>
#include <chrono>

using namespace std;

/**
* @brief tbb::parallel_invoke
* ****************************************************************************************/
#if 0
int main(){
  std::string s = "hello, world";

  char ch = 'd';

  tbb::parallel_invoke([&]{
    for (size_t i=0; i<s.size()/2; ++i){
      if (s[i] == ch)
        cout<<"found!"<<endl;
    }
  }, [&]{
    for (size_t i=s.size()/2; i<s.size(); ++i){
      if (s[i]==ch)
        cout<<"found!"<<endl;
    }
  });
  return 0;
}
#endif

/**
* @brief 任务组
* ****************************************************************************************/
void download(std::string file){
  for(int i=0; i<10; ++i){
    cout<<"Downloading "<<file<<"("<<i*10<<"%)..."<<endl;
    this_thread::sleep_for(chrono::milliseconds(400));
  }
  cout<<"Download complete: "<<file<<endl;
}

void interact(){
  string name;
  cin>>name;
  cout<<"hi, "<<name<<endl;
}

int main(){
  tbb::task_group tg;
  tg.run([&]{
    download("hello.zip");
  });
  tg.run([&]{
    interact();
  });
  tg.wait();
  return 0;
}