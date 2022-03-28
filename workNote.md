并发编程
---
关键词: mutex, RAII, lock_guard, unique_lock

`#include <thread>`管理线程的函数及类，不包含保护共享数据的类

每个线程需要一个**初始函数**`initial function`
初始线程是`main()`，其余线程可在std::thread对象的构造函数中指定

创建新线程之后，初始线程依旧继续进行，可能会在创建的新线程结束前结束
因此，调用`join()`，导致调用线程等待与`std::thread`对象相关联的线程

启动线程
---
线程在创建`std::thread`对象时启动
`thread`可调用类型构造，将含有函数调用符类型的实例传入`thread`类，替换默认构造函数







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


thread
---
单个执行线程，**线程允许多个函数同时执行**
线程在构建关联的线程对象时，**立即开始执行**
顶层函数可通过`std::promise`或**修改共享变量**将返回值或异常传递给调用方

- detach：从thread对象分离执行线程，调用detach后,`*this`不再占有线程



future
---
用于获取异步任务的返回值

promise：存储一个值，以进行异步获取


期物：线程A中启动线程B，需要但不立即需要B的返回结果
即A希望在**未来某个时刻**获得B的返回值

