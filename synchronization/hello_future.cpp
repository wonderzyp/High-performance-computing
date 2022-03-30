/**
* @brief future
* ****************************************************************************************/


// #include <future>
// #include <iostream>
// #include <chrono>

// int find_the_answer_to_ltuae(){
//   // std::this_thread::sleep_for(std::chrono::seconds(3));
//   return 42;
// }

// void do_other_stuff(){
//   printf("just wasting time :) \n");
//   std::this_thread::sleep_for(std::chrono::seconds(3));
// }

// // 使用future获取异步任务的返回值
// int main()
// {
//   std::future<int> the_answer=std::async(find_the_answer_to_ltuae);

//   do_other_stuff();
  
//   std::cout<<"The answer is "<<the_answer.get()<<std::endl;
// }

#include <string>
#include <future>

struct X
{
  void foo(int,std::string const&);
  std::string bar(std::string const&);
};

struct Y
{
  double operator()(double);
};

class move_only
{
public:
  move_only();
  move_only(move_only&&);
  move_only(move_only const&) = delete;
  move_only& operator=(move_only&&);
  move_only& operator=(move_only const&) = delete;
  void operator()();
};


int main()
{
  X x;

  auto f1=std::async(&X::foo,&x,42,"hello");  // 调用p->foo(42, "hello")，p是指向x的指针
  auto f2=std::async(&X::bar,x,"goodbye");  // 调用tmpx.bar("goodbye")， tmpx是x的拷贝副本

  Y y;
  auto f3=std::async(Y(),3.141);  // 调用tmpy(3.141)，tmpy通过Y的移动构造函数得到
  auto f4=std::async(std::ref(y),2.718);  // 调用y(2.718)
  
  X baz(X&);
  std::async(baz,std::ref(x));  // 调用baz(x)
  auto f5=std::async(move_only());  // 调用tmp()，tmp是通过std::move(move_only())构造得到
}



