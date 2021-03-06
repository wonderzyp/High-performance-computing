时间相关
---
C语言无类型区分，易弄错单位，混淆时间点和时间段
如乘法操作对时间而言没有意义

C++11引入 std::chrono
- 区分时间点和时间段，区分时间单位

`duration_cast`
`milli`
`sleep_for`
`sleep_until`


CTAD, compile-time argument deduction
---
编译期参数推断


封装
---
将一些**相关的量**封装在一起，类似**原子性**的设计
假设两个量是相互关联的，修改另一个量必然需修改另一个量
因此，尽量避免直接修改成员变量，而是通过成员函数修改


RAII
---
资源获取视为初始化，资源释放视为销毁
RAII是异常安全(exception-safe)的，保证异常发生时，会调用已创建对象的析构函数


构造函数
---
#### 初始化列表
- 更高效：避免先初始化再复制
- 可初始化成员常量或引用的值

初始化列表按**顺序**给对象每个成员赋值

初始化列表可实现**函数多返回值**

当自定义构造函数后，无法自动生成默认构造函数
使用`=default`可再次生成

拷贝构造函数：未初始化时，将另一个类拷贝进来用于初始化

拷贝赋值函数：已初始化时，**销毁**当前类，并拷贝另一个类

拷贝赋值约等于 拷贝构造 + 析构函数


#### 避免隐式类型转换
单个参数的构造函数可能存在隐式类型转换，造成意外情况
`explicit`：
- 必须强制显式转换
- 对多个参数起作用，禁止一个`{}`的初始化

注：调用构造函数时，`{}`比`()`更安全，`{}`是非强制类型转换，不能从float向int转换

#### POD, plain-old-data陷阱
int, float, double基础类型
void*, Object*等指针类型
及完全由这些类型组成的类，被称为POD
这些类型**不会被初始化为0**
避免POD陷阱：每个基础类型都使用`{}`


内存管理
---
- unique_ptr
曾经释放指针后需置为`NULL`，现在`p=nullptr`直接完成释放操作
将两操作合并，体现RAII的封装思想

禁止拷贝：删除了拷贝构造函数
解决方案：
1. 通过`get()`获得指针，但并不对管控指针的生命周期
2. 通过`std::move()`接管指针

- shared_ptr


模板
===

编译期常量
---
模板支持整形参数`template<int N>`，对于每个不同的N，模板均会生成一份代码，可进行单独的优化

模板的定义与实现需同时放在头文件，因此过度使用模板会导致二进制文件大小激增

编译器对模板的编译是**惰性**的：只有当前文件用到了模板，对应的模板参数才会被定义。

模板的惰性：延迟编译
---
当模板未被使用时，编译器不会对其实际编译


自动类型推导
===

限制：
1. 类成员不可定义为auto
2. 定义与实现分离，不可声明auto

decltype: 获取变量或表达式类型

万能推导：`decltype(auto)`
对于一个表达式，无法确定是可变引用、常引用、右值引用等等
`decltype(auto) p = func();`

函数可作为模板参数，编译器可针对不同函数编译特定版本并进行优化


lambda表达式
---
需保证lambda表达式生命周期不超过其引用捕获的变量
```cpp
auto make_twice(int fac){
  return [&](int n){ // [&]捕获fac的地址
    return n*fac;
  };
}
```
上述案例中，捕获的fac参数在`make_twice`返回时已经失效

lambda配合模板使用
```cpp
auto twice = [](auto n){
  return n*2;
};
```
等价于：
```cpp
template <class T>
auto twice(T n){
  return n*2;
}
```
同样有惰性、多次编译的特性