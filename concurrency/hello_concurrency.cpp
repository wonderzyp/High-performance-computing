#include <iostream>
#include <thread>

void hello()
{
  std::cout<<"hello cocurrent world\n";
}

void hello_withArgs(int a)
{
  printf("received %d\n", a);
}

class Hello_class
{
public:
  void operator()() const{
    std::cout<<"hello cocurrent world created by class\n";
  }
};

//Class for RAII example
class Thread_guard
{
  std::thread& t;
public:
  explicit Thread_guard(std::thread& t_): t(t_){};
  
  ~Thread_guard()  // 在析构函数里调用join()
  {
    if (t.joinable())  // 先判断线程是否已经join()，因为线程仅可被join一次
    {
      t.join(); 
    }
  }

  // 避免编译器自动生成拷贝构造和拷贝赋值函数
  // 直接对一个对象进行拷贝或赋值，可能会丢失已加入的线程
  // 声明delete后，任何对thread_guard对象的赋值操作会引发编译错误
  Thread_guard(Thread_guard const&)=delete;
  Thread_guard& operator=(Thread_guard const&)=delete;
};



int main()
{

  std::cout<<"Tips 1: three methods to launch threads\n";
  {
    std::thread t(hello);         // 普通函数

    Hello_class myclass;
    std::thread t_class(myclass); // 传入functor

    std::thread t_lambda([]{ std::cout<<"hello cocurrent world created by lambda\n";}); // lambda

    t.join();
    t_class.join();
    t_lambda.join();
  }
  std::cout<<std::endl;

  std::cout<<"Tips 2: try-catch\n";
  {
    Hello_class try_catch_threads;
    std::thread t_try_catch_threads(try_catch_threads);

    // std::thread t_try_catch_threads(Hello_class{});   // 或者使用大括号的匿名类

    try
    {
      hello();
    }
    catch(...)
    {
      t_try_catch_threads.join(); // 有异常则在此等候
      throw;
    }
    t_try_catch_threads.join(); // 正常情况下
  }


  std::cout<<std::endl;
  std::cout<<"Tip 3: RAII\n";
  {
    //使用事先定义的Thread_guard类
    std::thread RAII_thread(hello);
    Thread_guard g(RAII_thread);
  }
  
  std::cout<<std::endl;
  std::cout<<"Tips 4: pass functions with Args\n";
  {
    std::thread thread_withArgs(hello_withArgs, 4);
    thread_withArgs.join();
  }

}