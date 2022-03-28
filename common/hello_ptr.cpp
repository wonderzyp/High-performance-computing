#include <iostream>
#include <vector>
#include <memory>
#include <cstdio>
#include <fstream>
#include <cassert>
#include <functional>

/**
* @brief unique_ptr
* ****************************************************************************************/
struct B {
  virtual void bar() { std::cout << "B::bar\n"; }
  virtual ~B() = default;
};
struct D : B
{
    D() { std::cout << "D::D\n";  }
    ~D() { std::cout << "D::~D\n";  }
    void bar() override { std::cout << "D::bar\n";  }
};

std::unique_ptr<D> pass_through(std::unique_ptr<D> p){
  p->bar();
  return p;
}


int main()
{
  // auto p = std::make_unique<D>(); // p占有D
  // auto q = pass_through(std::move(p)); // 此处为何move右值？
  // assert(!p); // p不占用对象，且保留空指针
  // q->bar();

  std::unique_ptr<B> p = std::make_unique<D>(); // p 占有D, 但指向基类
  p->bar();

  std::vector<std::unique_ptr<B>> v;
  v.push_back(std::make_unique<D>());
  v.push_back(std::move(p));
  v.emplace_back(new D);
  for (auto& elem : v) elem->bar();




}