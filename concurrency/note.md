对线程间进行同步：某个线程需等待另一个线程完成（或某些特定事件的发生）

**条件变量**、**期望**

选择1：不断询问，浪费资源
2：指定周期性歇息时间，但sleep时间的选择至关重要
3：C++标准库提供的工具--条件变量

条件变量
---
`std::condition_variable`成员函数：
- `wait()`传递一个锁和一个lambda表达式作为等待条件，条件满足时返回
若条件不满足，解锁互斥量，阻塞该线程
当被notify_one()通知时，线程从睡眠中苏醒并获取互斥锁，并检测条件
条件满足时从wait返回并继续持有锁，条件不满足则解锁并继续等待
- `notify_one()`通知所有等待的线程

> 似乎`notify_one()`是无差别通知，具体是否执行由线程自身判断

`std::lock_guard`不如`std::unique_lock`灵活，由于线程在等待期间需频繁地解锁上锁，故选择`std::unique_lock`
如果选择使用`std::lock_guard`，线程在休眠中依旧对互斥量上锁，此时前置线程无法正常处理任务，如此休眠线程的条件永远无法满足

`wait()`可传任意函数，需注意函数中不能有副作用（有点类似assert）
调用`wait`时，一个条件变量可能去检查给定条件**若干次**，若传入的函数有副作用，可能在唤醒前执行多次


等待线程仅等待一次，条件为`true`时，不会再等待条件变量


future-期望
---
future:提供访问异步操作结果的机制，通过async, packaged_task或promise创建
可查询、等待或从std::future中提取值，若依旧未提供值，可能会**阻塞**

async使用时不需要绑定线程
packaged_task和promise可绑定

#### `std::packaged_task`
将可调用对象进行包装

#### `std::promise`
提供存储值或异常的设施，每个promise与共享状态关联
promise可对共享状态做三件事：
- 使就绪
- 释放
- 抛弃




当一个线程需等待一个特定的一次性事件时
在等待任务期间，可先执行其余的一些任务，直到对应的任务触发

唯一期望
共享期望

`std::future`的实例仅与一个指定事件相关联

`std::launch::async`
`std::launch::deferred`：函数调用被延迟到`wait`或`get`函数调用时执行

std::packaged_task
---
用于包装任何可调用**callable**目标（函数、lambda表达式、bind表达式或其余函数对象），使得可异步调用，其返回值或所抛异常存储于std::future对象访问的共享状态中


`std::promises`：
上下文频繁切换（线程数量超出硬件的可接受并发数）
每个promise与共享状态关联，可对共享状态做三件事：
1. 使就绪：
2. 释放：放弃对共享状态的引用
3. 抛弃：



记录多线程模块的使用方式
---

std::lock_guard
---
提供RAII风格的互斥功能，传入一个互斥量作为参数
```cpp
int g_i;
std::mutex g_i_mutex;
std::lock_guard<std::mutex> lock(g_i_mutex); // 传入将被保护的互斥量
```


std::condition_variable
---
`std::condition_variable`类是个同步原语，用于阻塞部分线程，直到另一线程修改共享变量并通知
准备修改变量的线程需：
1. 获得`std::mutex`
2. 在保有锁时进行**修改**
3. 在`std::condition_variable`上执行`notify_one`或`notify_all`

在`std::condition_variable`上等待的线程需执行：
1. 检查条件，是否为已更新或提醒它的情况
2. 执行`wait`,  `wait_for`或`wait_until`，等待操作自动释放互斥
3. `std::condition_variable`被通知时，线程被唤醒且自动获得互斥，检查条件发现虚假唤醒，则继续等待



#### notify
通知在条件变量上阻塞的线程（条件变量的值已满足相应要求）
相应的要求在wait()中定义（一般用lambda表达式）
##### notify_one
调用notify_one会解阻塞在条件变量上等待的线程之一
调用notify_one通知前，通知线程不必再保有等待线程所保有的同一互斥量上的锁，以避免刚被通知即再次阻塞，可在通知前**解开互斥锁**
```cpp
std::unique_lock<std::mutex> lk(cv_m); // cv_m是互斥量
lk.unlock(); // 通知前解开锁
cv.notify_one();
```
##### notify_all
类似`notify_one`，但此方法可唤醒多个阻塞线程

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
`std::thread::hardware_concurrency()`：返回硬件核心数
可通过设置单个线程处理的最小数据量，避免切换上下文成本大于计算成本
`max_threads = (length + min_per_thread-1)/min_per_thread`

线程标识
---
`std::this_thread::get_id()`或对thread对象调用成员函数`.get_id()`
C++标准要求ID相等的线程必须有相同的输出





