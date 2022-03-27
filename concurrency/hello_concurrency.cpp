#include <iostream>
#include <thread>

void hello()
{
  std::cout<<"hello cocurrent world\n";
}

class Hello_class
{
public:
  void operator()() const{
    std::cout<<"hello cocurrent world created by class\n";
  }
};

int main()
{
  std::thread t(hello);         // 普通函数

  Hello_class myclass;
  std::thread t_class(myclass); // 传入functor

  std::thread t_lambda([](){ std::cout<<"hello cocurrent world created by lambda\n";}); // lambda

  t.join();
  t_class.join();
  t_lambda.join();
}