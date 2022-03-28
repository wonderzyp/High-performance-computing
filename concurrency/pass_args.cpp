#include <iostream>
#include <thread>

class TestNum
{
public:
  int a;
  int b;
};

class TestMemberFun
{
  public:
    void fun(){
      printf("\nhello\n");
    }
};


void fun(TestNum& test)
{
  test.a += 10;
  printf("a= %d\n",test.a);
}


int main()
{

  std::cout<<"Tip 1: std::ref\n";
  {
    TestNum num_notRef;
    num_notRef.a=1;
    num_notRef.b=2;

    std::thread t1(fun,std::ref(num_notRef));
    std::thread t2(fun, std::ref(num_notRef));
    std::thread t3(fun, std::ref(num_notRef));

    t1.join();
    t2.join();
    t3.join();
  }
  std::cout<<std::endl;

  std::cout<<"Tip 2: pass member function\n";
  {
    TestMemberFun m_fun;
    std::thread t_mfun(&TestMemberFun::fun, m_fun); // 传递成员函数
    t_mfun.join();
  }
  std::cout<<std::endl;
}





