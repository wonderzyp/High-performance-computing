/**
* @brief future
* ****************************************************************************************/
#include <future>
#include <iostream>
#include <chrono>

int find_the_answer_to_ltuae(){
  // std::this_thread::sleep_for(std::chrono::seconds(3));
  return 42;
}

void do_other_stuff(){
  printf("just wasting time :) \n");
  std::this_thread::sleep_for(std::chrono::seconds(1));
}

struct Point
{
  int x, y;
  Point(int x_, int y_) : x(x_), y(y_) {};

  void pass_args(int a){
  printf("pass args with std::async and add one\n");
  x+=a;
  y+=a;
  }
};

int main()
{
  // examples on cpp-reference
  {
    // packaged_task
    std::packaged_task<int()> task([](){return 7;});
    std::future<int> f1 = task.get_future(); // 获取future
    std::thread(std::move(task)).detach();
  
    //async()
    std::future<int> f2 = std::async(std::launch::async, [](){return 8;});

    //promise
    std::promise<int> p;
    std::future<int> f3=p.get_future();
    std::thread( [&p]{p.set_value_at_thread_exit(9);}).detach();

    std::cout<<"Waiting..."<<std::endl;
    f1.wait();
    f2.wait();
    f3.wait();
    std::cout << "Done!\nResults are: "
          << f1.get() << ' ' << f2.get() << ' ' << f3.get() << '\n';
    
    return 0;
  }




  // 使用future获取异步任务的返回值
  {
    std::future<int> the_answer=std::async(find_the_answer_to_ltuae);
    do_other_stuff();
    std::cout<<"The answer is "<<the_answer.get()<<std::endl;
  }
  
  // std::async传参
  std::cout<<std::endl;
  {
    Point my_point(10,20);
    std::future<void> pass_args = std::async(&Point::pass_args, &my_point, 11);
    do_other_stuff();
    std::cout<<"after passing x= "<<my_point.x<<"y= "<<my_point.y<<std::endl;
  }
}

