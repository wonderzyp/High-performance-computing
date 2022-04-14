线程相关
---
join: 等待
thread遵循三五法则和RAII思想
因为管理着资源，自定义解构函数，删除拷贝构造/赋值函数，提供移动构造/赋值函数

将某个线程托管至thread类时，离开类的作用域会自动调用析构函数，销毁线程
通过`detach`将线程和托管类分离，可将线程生命周期延长至构造函数外
线程不再由类管理，而在结束时自动退出

但主线程并不会等所有子线程执行完毕后再退出，因此detach分离后的线程可能无法执行

定义一个全局变量作为线程池，将想要detach的线程move到线程池中；
且设计线程池时，析构函数自动join

C++20引入`std::jthread`


异步
---
#### `std::async`
接受一个带返回值的lambda，返回`std::future`对象
该lambda在**另一个线程**中运行

可对future执行`get`或`wait`
- get会获取返回值，而wait仅仅等待执行完毕
- wait会一直等待下去，wait_for可指定等待时间
- wait_for按等待结果不同，返回future_status::time_out或future_status::ready


async第一个参数可以是`std::launch::deferred`，不会立即创建线程执行任务，而是将**计算推迟**到调用get时
惰性求值(lazy evaluation)

异步有点像**带返回值**的thread类

#### std::promise
`async`会自动创建线程，而`promise`可手动管理线程
`promise`通过`set_value()`设置返回值


`future`为了三五法则，删除拷贝构造、赋值函数
若需要浅拷贝，可使用`std::shared_future`


互斥量
---
lock_guard使用RAII思想自动上锁解锁，但严格限制仅在析构时解锁
`unique_lock`可更加灵活地管理互斥量
unique_lock额外存储一个flag标明是否被释放，析构时检查该flag，若已被释放，则不会调用`unlock()`
第二个参数可接受`std::defer_lock`，标明不在构造函数中上锁
> 使用空tag类区分不同的构造函数

try_lock(): 如果上锁失败，不会像`lock()`一样阻塞等待
try_lock_for, try_lock_until


