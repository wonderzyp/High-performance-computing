#include <atomic>
#include <iostream>
using namespace std;

int main()
{
  boolalpha(std::cout); // 将bool值显示为true或false
  std::atomic<int> counter;

  counter.store(2);
  int old = 1;
  // compare_exchange_strong(old, val)取原子变量的值
  // 将原子变量与old比较，若不相等则将原子变量值写入old
  // 若相等，则将val写入原子变量
  bool equal = counter.compare_exchange_strong(old, 3);
  cout<< "equal= "<<equal<<endl;
  cout<<"old= "<<old<<endl;

  int now = counter.load();
  cout<<"cnt= "<<now<<endl;
  
  old = 2;
  // 此时原子变量与old值相等
  equal = counter.compare_exchange_strong(old, 3);
  cout<< "equal= "<<equal<<endl;
  cout<<"old= "<<old<<endl;

  now = counter.load();
  cout<<"cnt= "<<now<<endl;

}