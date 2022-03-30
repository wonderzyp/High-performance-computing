/**
* @brief explicit 抑制类构造函数的自动隐式转换，防止意料之外的错误发生
* ****************************************************************************************/


#include <iostream>

class A
{
public:
  A(int a_=855) : m_a(a_){};
  int getA(){
    return m_a;
  }
private:
  int m_a;
};

class A_withExplicit
{
public:
   explicit A_withExplicit(int a_=855) : m_a(a_){};
     int getA(){
    return m_a;
  }
private:
  int m_a;
};



int main()
{
  A normal_a;
  normal_a=10; // 虽然未重载'=',但可将int类型赋值给对象A
               // 进行隐式转化 normal_a = A temp(10);

  A_withExplicit explicit_a;
  // explicit_a=10;                     //  不允许转换
  // explicit_a = A_withExplicit(10);   // 可显式转换

  printf("normal m_a: %d\n", normal_a.getA());
  printf("explicit m_a: %d\n", explicit_a.getA());
}