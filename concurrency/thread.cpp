/**
* @brief 模拟多线程场景：执行下载任务时，需响应鼠标点击
* ****************************************************************************************/
#include <iostream>
#include <thread>
#include <string>
#include <vector>
using namespace std;

class ThreadPool{
  vector<thread> m_pool;
public:
  void push_back(std::thread thr) {
    m_pool.push_back(std::move(thr));
  }

  ~ThreadPool(){
    for (auto &t:m_pool) t.join();
  }
};

ThreadPool tpool;


void download(std::string file){
  for (int i=0; i<10; ++i){
    cout<<"Downloading "<<file
        <<"("<<i*10<<"%)..."<<endl;
  }
  cout<<"Download complete: "<<file<<endl;
}

void interact(){
  cout<<"I know you click me"<<endl;
}

void myfun(){
  thread t1([&]{
    download("hello.zip");
    });
  // t1.detach(); // 避免退出函数体时，t1被析构
  tpool.push_back(std::move(t1)); // 将控制权转移给全局pool, 延长生命周期
}


/**
* @brief C++20 引入std::jthread
* ****************************************************************************************/

// std::vector<std::jthread> jpool; //jthread未找到

// void myfunc_j(){
//   jthread t1([&]{
//     download("hello.zip");
//     });
//   jpool.push_back(std::move(t1));
// }


int main(){
  myfun();
  interact();
  return 0;
}

