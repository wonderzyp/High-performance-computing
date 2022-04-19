#include <iostream>
#include <string>
#include <tbb/parallel_invoke.h>
using namespace std;

/**
* @brief tbb::parallel_invoke
* ****************************************************************************************/
#if 0
int main(){
  std::string s = "hello, world";

  char ch = 'd';

  tbb::parallel_invoke([&]{
    for (size_t i=0; i<s.size()/2; ++i){
      if (s[i] == ch)
        cout<<"found!"<<endl;
    }
  }, [&]{
    for (size_t i=s.size()/2; i<s.size(); ++i){
      if (s[i]==ch)
        cout<<"found!"<<endl;
    }
  });
  return 0;
}
#endif

