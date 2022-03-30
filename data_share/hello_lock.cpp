#include <mutex>
#include <thread>
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;
using std::cin;

class Points
{
public:
  Points(int x_, int y_): x(x_), y(y_){};
  int x,y;
};

void swap(Points& lhs, Points& rhs){
  int tempx = lhs.x;
  int tempy = lhs.y;

  lhs.x = rhs.x;  lhs.y = rhs.y;
  rhs.x = tempx;  rhs.y = tempy;
}


class MyClass
{
private:
  Points point;
  std::mutex m;
public:
  MyClass(Points& p) : point(p) {};

  friend void swap(MyClass& lhs, MyClass& rhs){
    if (&lhs == &rhs) return; // 避免自交换时重复上锁

    std::lock(lhs.m, rhs.m);

    std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);
    std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);
    swap(lhs.point, rhs.point);
  }

  void getPoints(){
    printf("x= %d, y=%d\n", point.x, point.y);
  }
};



int main()
{
  Points points1(9,99);
  Points points2(1,11);

  MyClass myclass1(points1);
  MyClass myclass2(points2);

  printf("the original datas:\n");
  myclass1.getPoints();
  myclass2.getPoints();

  std::thread t1(swap, &myclass1, &myclass2);


  swap(myclass1, myclass2);

  printf("After operator datas:\n");
  myclass1.getPoints();
  myclass2.getPoints();

}


/**
* @brief 一次性锁住多个互斥量，避免死锁
* ****************************************************************************************/