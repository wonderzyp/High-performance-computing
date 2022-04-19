本仓库通过各类实例学习**C++并发编程**及**C++新特性**
===

并发编程(concurrency文件夹内)
---
C++11新标准添加以下并发相关的类
- 管理线程
- 保护共享数据
- 线程间同步操作
- 低级原子操作：直接控制单个位、字节、内部线程间同步

#### 管理线程
- thread类的使用：绑定函数、functor、lambda表达式等
- 线程传参：thread类基于`std::bind`实现
- 线程移动：`std::move`, `std::ref`
- 线程数量：单个线程任务不可太少
- 线程标识：`std::this_thread::get_id()`和成员函数`.get_id()`

#### 保护共享内存
- mutex类：
- 避免几种使mutex失效的情况：成员函数返回保护变量的指针
- unique_lock: 可移动不可复制
- shared_lock

`hello_mutex.cpp`：以10000次循环+1操作为例，发现不使用mutex的结果不正确


模板
---

模板特化





STL
---

Lambda表达式
---
