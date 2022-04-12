/**
* @brief 获取时间
* ****************************************************************************************/

#include <chrono>
#include <iostream>
#include <thread>
using namespace std;

int main()
{
  /**
  * @brief 简单使用chrono计时
  * ****************************************************************************************/
  {
    auto t0 = std::chrono::steady_clock::now();
    auto t1 = t0 + chrono::seconds(30);
    auto dt = t1-t0; // 获取时间段

    // 获取时间段的秒数
    int64_t sec = chrono::duration_cast<chrono::seconds>(dt).count();
    cout<<sec<<endl;
  }

  {
    auto t0 = chrono::steady_clock::now();
    for (volatile int i=0; i<100000; ++i);
    auto t1 = chrono::steady_clock::now();
    auto dt = t1-t0;

    // milli: 毫秒
    // micro: 微秒
    // 默认值: 秒
    // duration_cast可实现任意duration类型之间的转换
    using double_ms = chrono::duration<double, milli>;
    double ms = std::chrono::duration_cast<double_ms>(dt).count();
    std::cout<<"time elapsed: "<<ms<<"ms"<<endl;
  }

  /**
  * @brief sleep_for and sleep_until
  * ****************************************************************************************/
  {
    cout<<"sleep for 1000ms"<<endl;
    std::this_thread::sleep_for(chrono::milliseconds(1000));
    cout<<"finished"<<endl;

    cout<<"sleep for 2000ms"<<endl;
    auto t = chrono::steady_clock::now()+chrono::milliseconds(2000);
    std::this_thread::sleep_until(t);
    cout<<"finished"<<endl;
  }

}