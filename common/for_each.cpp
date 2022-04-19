#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

int sum=0;
void func(int vi){
  sum += vi;
}

int main()
{
/**
* @brief for_each, 对容器上所有元素调用函数
* ****************************************************************************************/
#if 0
  vector<int> v = {4,3,2,1};
  for_each(v.begin(), v.end(), func);

  cout<<sum<<endl;
  return 0;
#endif

/**
* @brief CTAD, 编译期类型推断
* ****************************************************************************************/
#if 0
  std::vector v = {1,2,3,4}; // c++17后，vector可不显式指定类型
  int sum=0;
  std::for_each(v.begin(), v.end(), [&](auto vi){
    sum+=vi;
  });

  cout<<sum<<endl;
  return 0;
#endif

/**
* @brief c++17以后引入数值算法
* #include <numeric>
* ****************************************************************************************/
#if 0  
  std::vector v = {1,2,3,4};
  int sum = std::reduce(v.begin(), v.end());
  cout<<sum<<endl;
#endif


}