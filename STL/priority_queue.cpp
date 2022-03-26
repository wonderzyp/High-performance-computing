#include <queue>
#include <iostream>

template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}


int main(){
  std::priority_queue<int> q;
  for(int n : {1,8,5,6,3,4,0,9,7,2})
      q.push(n);
  print_queue(q);

  std::priority_queue<int, std::vector<int>, std::greater<int> > q2;
  for(int n : {1,8,5,6,3,4,0,9,7,2})
      q2.push(n);
  print_queue(q2);


  auto cmp_lambda = [](int left, int right){return (left>right);};
  std::priority_queue<int, std::vector<int>, decltype(cmp_lambda)> q3(cmp_lambda);
    for(int n : {1,8,5,6,3,4,0,9,7,2})
    q3.push(n);

    print_queue(q3);

}