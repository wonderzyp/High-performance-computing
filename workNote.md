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


C++ most vexing parse
---
编译器无法分清两种情况：
- 对象参数的创建
- 函数类型的规约

```cpp
//eg 1: 
int i(int(my_db));
// 解释1：用强制类型转换后的my_db初始化变量i
// 解释2：声明函数 int i(int my_db);  默认采取
// c++允许参数被多余括号包围

//eg 2:
struct Timer{};
struct TimeKeeper{};

TimeKeeper t(Timer());
// 解释1：使用匿名类Timer()初始化t
// 解释2：声明函数t，其有一个匿名参数，该参数类型为"无参数、返回类型为Timer"的函数指针，函数t的返回类型是TimeKeeper的类对象
```