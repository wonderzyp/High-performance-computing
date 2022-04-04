并发数据结构的设计、并发代码设计


并发数据结构设计
---
若一种数据结构可被多个线程访问，且值可能会发生变化，此时需对数据结构进行正确的设计
目的：多线程环境下可**正确的同步**
手段：
- 独立的互斥量
- 设计能够并发访问的数据结构

#### 数据结构并发设计的意义
并发数据结构允许多个线程并发地进行访问
多线程下无数据丢失和损毁、无条件竞争

#### 实例1：线程安全栈
互斥量m保证基本的线程安全，对每个成员函数加锁保护，则同一时刻仅一个线程可访问到数据
如此，数据结构不变量被破坏时，其余线程不可见

`empty()`和`pop()`可能存在潜在的竞争，在pop上锁时，显式地查询栈是否为空，此处竞争非恶性

`pop()`对弹出值直接返回，可避免`std::stack`中top和pop成员函数之间的潜在竞争

##### 接口的潜在竞争：
`empty()`和`size()`在被调用并返回时是正确的，但其结果往往不可靠。
当它们返回后，其余线程可自由地访问栈（pop或push多个元素），如此，之前从empty或size中获取的结果存在问题
以下列代码块为例：
```cpp
stack<int> s;
if (! s.empty()){    // 1
  int const value = s.top();    // 2
  s.pop();    // 3
  do_something(value);
}
```
在操作1和2之间，可能有另一个线程执行了pop操作，如此top函数可能会作用于一个空栈，进而导致未定义行为。
如此，即使对特定变量进行保护，也无法阻止条件竞争的发生

此外，在操作2和3之间存在隐患
假设有两个线程a,b，均执行`top->pop`
我们希望`a.top->a.pop->b.top->b.pop`
但实际上可能`a.top->b.top->a.pop->b.pop`
虽然通过互斥量保证同一时刻仅一个线程可访问共享的成员变量，但成员函数之间依旧存在潜在的竞争

问题3：
当拷贝一个`vector`时，标准库会从堆上分配较多内存完成拷贝。但如果资源有限，会抛出`std::bad_alloc`异常

pop弹出返回值时，只有当值被返回到调用函数时，栈才会被改变。如果拷贝数据时抛出异常，弹出的值会消失，且从栈上消失，如此这个值不见了

因此，`std::stack`将操作分为`top`和`pop`两部分，即使无法完成安全拷贝，栈中数据依旧存在。
显然，这种设计导致了条件竞争

解决：
传入引用





异常源：
1. 对互斥量上锁可能抛出异常，但上锁是成员函数的第一个操作，极其罕见（问题出在系统资源上）
2. push可能抛出异常：内存不足或拷贝/移动数据值时
3. 



#### 实例2：线程安全队列



有以下两个考虑：
##### 访问是安全的（线程安全的）
- 数据结构中不变量被破坏时，不会有线程看见（类似临界区的感觉）
- 小心会引发条件竞争的接口
- 注意数据结构的行为是否会产生异常，进而影响“不变量”的稳定性
- 将死锁概率降至最低，避免嵌套锁的存在

##### 可真正的并发访问
- 锁范围中的操作，是否允许在锁外执行？
- 数据结构中不同区域是否可被不同的互斥量保护？
- 所有操作均需同级互斥量保护吗？

> 核心：最小化序列化访问，最大化真实并发



线程间划分工作
---
#### 并行化for_each
每个线程分配一定量的数据，并在各自的数据集上执行**相同**的操作

如果对一个很大的数据集进行排序，每层递归会产生一个新线程，最终生成大量线程而影响性能



考虑多性能性能的数据结构设计
---


有时类的拷贝无意义，如`std::mutex`
拷贝一个互斥量没有意义
`std::unique_lock<>`一个实例仅一个锁，仅转移实例的所有权有意义


锁粒度太小可能导致条件竞争
粒度太大可能影响性能

一个操作需两个及以上互斥量时，可能产生死锁
