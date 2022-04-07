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


