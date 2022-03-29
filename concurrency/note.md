`#include <thread>`
---
管理线程的函数及类，不包含保护共享数据的类

每个线程需要一个**初始函数**`initial function`
初始线程是`main()`，其余线程可在std::thread对象的构造函数中指定

创建新线程之后，初始线程依旧继续进行，可能会在创建的新线程结束前结束
因此，调用`join()`，导致调用线程等待与`std::thread`对象相关联的线程

启动线程
---
线程在创建`std::thread`对象时启动
`thread`可调用类型构造，将含有函数调用符类型的实例传入`thread`类，替换默认构造函数

需明确使用加入式or分离式，必须在thread对象析构前做出决定

避免使用一个可访问局部变量的函数去创建线程

#### 等待线程完成
join()仅是简单地等待完成
使用条件变量或期待，可更灵活地控制
调用join后，会清理线程相关的存储部分，thread对象将不再与已完成的线程有任何关联

只能对同一进程使用一次`join`
`join`调用前如果有异常抛出，则该次`join`调用会被跳过

RAII, Resource Acquisition Is Initialization
资源获取即初始化
通过类管理线程，析构函数保证join()必然被执行
> 析构函数中需先对线程进行joinable()判断，避免多次join()

#### 后台运行线程
detach()会使线程在后台运行，意味着主线程无法与之产生直接交互
分离线程又称**守护线程(daemon threads)**，UNIX中守护线程无显式的用户接口，
并在后台运行的线程，可长时间运行，监视文件系统、清理缓存等

不仅可向thread类的构造函数传递函数名，同时也可以传递参数

线程间参数的传递
---
默认参数要**拷贝**到线程独立内存中
避免期望传递引用，却复制了整个对象`std::ref`
> 函数式编程`std::bind`拷贝整个对象，而不是引用

传递成员函数
```cpp
  TestMemberFun m_fun;
  std::thread t_mfun(&TestMemberFun::fun, m_fun); // 传递成员函数
```
`m_fun`地址作为指针对象传递给函数
移动转移原对象后，会留下一个空指针`NULL`
临时变量自动进行移动操作
命名对象需`std::move`显式转化

thread可移动不可复制性（是否将拷贝构造函数给delete了？）


转移线程的所有权
---
资源占有(resource-owning)类型：`std::ifstream`,`std::unique_ptr`, `std::thread`
以上均是可移动但不可拷贝，**执行线程的所有权可在thread实例之间移动**

```cpp
std::thread t1(some_function);            // 1
std::thread t2=std::move(t1);            // 2
t1=std::thread(some_other_function);    // 3
```
第三步：所有者是临时对象时，隐式调用移动操作

- 不能已关联线程的thread类重复绑定线程
> 无法通过赋新值给`thread`对象来丢弃线程

运行时决定线程数量
---





