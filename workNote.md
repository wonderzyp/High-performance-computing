并发编程
---
关键词: mutex, RAII, lock_guard, unique_lock




`mutex`是并发技术的核心之一, c++11引入mutex相关类，且置于`<mutex>`头文件内
mutex可保护共享数据,避免数据被多个线程同时访问
调用mutex的线程,自lock或try_lock起,至unlock,该线程占有mutex
当在mutex被占有时,其他线程若试图要求mutex的所有权,会阻塞对lock的调用,或收到false

- lock() 上锁
- unlock() 解锁
编码时优先选择C++11提供的`std::lock_guard`等RAII语法模板类

>RAII(Resource Acquisition is Initialization),将使用前请求的资源的生命周期,与一个对象的生存期绑定
>- 将每个资源封装进一个类
>  - 构造函数无法完成时,*抛出异常*
>  - 析构函数,*绝不抛出异常*

std::unique_lock相对于std::lock_guard出现,该类型的对象以*独占所有权*的方式管理mutex对象的上锁与解锁操作

std::unique_lock可显式调用lock和unlock(lock_guard不行),**可缩小锁的范围,提升并发度**








> pthread库不是Linux默认的库，编译时添加-lpthread参数
