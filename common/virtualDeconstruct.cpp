#include <iostream>
using namespace std;


class Base
{
private:
  int *m_data;
public:
  Base(){
    cout<<"Base Construct"<<endl;
    m_data = new int(855);
  }
  virtual ~Base(){  // 可尝试将其去掉，观察结果
    cout<<"Base Deconstruct"<<endl;
    delete m_data;
  }
};

class Derived : public Base
{
private:
public:
  Derived(){
    cout<<"Derived Construct"<<endl;
  };
  ~Derived(){
    cout<<"Derived Deconstruct"<<endl;
  };
};

int main(){
  Base* ptr = new Derived();
  delete ptr;
}



