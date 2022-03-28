new表达式
---
创建并初始化拥有动态存储期的对象，此类对象的生存期不受创建时所在的作用域限制

new表达式尝试申请存储空间，在已申请的空间上尝试构造并初始化一个无名对象或数组
new返回一个指向它构造的对象或对象数组的**纯右值指针**

内存泄漏
---
new表达式创建的对象会持续到new返回的指针用于匹配的delete表达式之时
当指针原值丢失时，对象不可达且无法解分配，发生内存泄漏(memory leak)
```cpp
//指针赋值
int* p = new int(7);
p=nullptr;

//指针离开作用域
void f()
{
  int* p = new int(7);
}

void f()
{
  int* p = new int (7);
  g(); // 可能抛出异常
  delete p; //g()抛出异常则内存泄漏
}
```

为简化动态分配的对象管理，一般将new表达式的结果存储于智能指针中
std::unique_ptr和std::shared_ptr可保证在上述情形中执行delete表达式

unique_ptr
---
`std::unique_ptr`通过指针占有并管理另一对象，下述两情况会释放对象
- 销毁了管理的unique_ptr
- 使用operator=或reset()赋值另一指针给管理的unique_ptr对象

shared_ptr
---
通过指针保持对象共享所有权的智能指针，多个shared_ptr对象可占有同一对象
下述两情况会释放内存
- 最后剩下的占有对象的shared_ptr被销毁
- 最后剩下的占有对象的shared_ptr被operator=或reset()赋值为另一指针





