/**
* @brief 获取时间
* ****************************************************************************************/

#include <chrono>
#include <iostream>
using namespace std;

int main()
{
  auto t0 = std::chrono::steady_clock::now();
  auto t1 = t0 + chrono::seconds(30);
  auto dt = t1-t0; // 获取时间段

  int64_t sec = chrono::duration_cast<chrono::seconds>(dt).count();

  cout<<sec<<endl;
}