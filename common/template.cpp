#include <iostream>
#include <vector>

using namespace std;

/**
* @brief 模板的特化
* ****************************************************************************************/
#if 0
template <class T>
T twice(T t){
  return t*2;
}

// 和已有模板相互重载
std::string twice(std::string t){
  return t+t;
}

int main()
{
  cout<<twice(1)<<endl;
  cout<<twice(std::string("abc"))<<endl;
}
#endif

/**
* @brief 整数可作为模板参数
* ****************************************************************************************/
#if 0
template <int N>
void show_times(std::string msg){
  for (int i=0; i<N; ++i){
    cout<<msg<<endl;
  }
}

int main()
{
  show_times<3>(std::string("zyp is handsome"));
}
#endif

/**
* @brief 模板部分特化：仅能泛化vector内部元素类型
* ****************************************************************************************/
#if 0
template <class T>
T sum(std::vector<T> const &arr){
  T res =0;
  for (int i=0; i<arr.size(); ++i){
    res+=arr[i];
  }
  return res;
}
#endif

/**
* @brief c++17: 编译期分支(if constexpr)
* ****************************************************************************************/
#if 0
template <bool debug>
int sumto(int n){
  int res=0;
  for (int i=1; i<=n; ++i){
    res += i;
    if constexpr (debug)
      std::cout<<i <<"-th: "<<res<<endl;
  }
  return res;
}

int main(){
  cout<<sumto<true>(4)<<endl;
  cout<<sumto<false>(4)<<endl;

  constexpr bool debug = true;
  cout<<sumto<debug>(5)<<endl;
}
#endif

/**
* @brief 模板惰性：延迟编译
* main()未调用对应模板，因此甚至不会被实际编译
* ****************************************************************************************/
#if 0
template <class T = void>
void fun_never_compile(){
  "字符" = 21123;
}

int main(){
  return 0;
}
#endif

/**
* @brief 模板函数+运算符重载
* ****************************************************************************************/
#if 0
template <class T>
std::ostream &operator<<(std::ostream &os, std::vector<T> const &a){
  os<<"{";
  for (size_t i=0; i<a.size(); ++i){
    os<<a[i];
    if (i != a.size()-1)
      os<<", ";
  }
  os<<"}";
  return os;
}

int main(){
  vector<int> a{1,2,3,4,5};
  vector<double> b{1.21,2.305,31.5};
  cout<<a<<endl;
  cout<<b<<endl;
}
#endif

/**
* @brief 万能推导, decltype(auto)
* ****************************************************************************************/
#if 0
template<class T1, class T2>
auto add(std::vector<T1> const &a, std::vector<T2> const &b){
  using T0 = decltype(T1{} + T2{});
  std::vector<T0> ret;
  
  for (size_t i=0; i<std::min(a.size(), b.size()); ++i){
    ret.push_back(a[i] + b[i]);
  }
  return ret;
}

int main(){
  vector<int> a = {2,3,4};
  vector<float> b = {0.5f, 1.0f, 2.0f};
  auto c = add(a,b);
  for (size_t i=0; i<c.size(); ++i)
    cout<<c[i]<<endl;
}
#endif

/**
* @brief 函数可作为模板参数
* ****************************************************************************************/
#if 0
void print_float(float n){
  printf("float %f\n", n);
}

void print_int(int n){
  printf("int %d\n", n);
}

template <class Func>
void call_twice(Func func){
  func(0);
  func(1);
}

int main(){
  call_twice(print_float);
  call_twice(print_int);
  return 0;
}
#endif

/**
* @brief lambda表达式的[&]引用捕获，需保证被捕获变量的生命周期长于lambda表达式
* ****************************************************************************************/
#if 0
template <class Func>
void call_twice(Func const &func){
  cout<<func(0)<<endl;
  cout<<func(1)<<endl;
  cout<<"Func大小: "<<sizeof(Func)<<endl;
}

auto make_twice(int fac){
  return [&](int n){ // [&]捕获fac的地址
    return n*fac;
  };
}

int main(){
  auto twice = make_twice(2);
  call_twice(twice);
  return 0;
}
#endif

