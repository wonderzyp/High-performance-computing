#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


/**
* @brief 串行缩并：时间复杂度O(n), 工作复杂度O(n)
* ****************************************************************************************/
int main(){
  size_t n = 1<<26;
  float res = 0;

  for (size_t i=0; i<n; ++i){
    res += sin(i);
  }
  cout<<res<<endl;
}