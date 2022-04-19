#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
using namespace std;

/**
* @brief 初始化列表返回多个值
* ****************************************************************************************/
struct Test{
  bool m_bool;
  int m_int;
  float m_float;
};

Test fun(){
  return {true, 1, 1.202f};
}

int main(){
  auto ret = fun();
  if (ret.m_bool == true){
    cout<<ret.m_int<<" "<<ret.m_float<<endl;
  }
}




#if 0
class Pig{
public:
  const string m_name;
  int m_weight;
  Pig() : m_name("aha"), m_weight(80)
  {}
};

int main(){
  Pig pig;
  cout<<"name: "<<pig.m_name<<endl;
  cout<<"weight: "<<pig.m_weight<<endl;

  // {}非强制转换
  int a{10.0f}; // 不通过, narrowing conversion
  // float a{10};
  cout<<"a= "<<a<<endl;
}
#endif 

/**
* @brief POD陷阱
* ****************************************************************************************/
#if 0
class Pig{
public:
  string m_name;
  int m_weight{0};
};

int main(){
  // POD, plain-old-data
  Pig pig;
  cout<<"name: "<<pig.m_name<<endl;
  cout<<"weight: "<<pig.m_weight<<endl;
}
#endif
