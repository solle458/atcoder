#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main(){
  int Q;
  cin >> Q;
  priority_queue<int, vector<int>, greater<int>> pq;
  for(int q = 0; q < Q; q++){
    int v, x;
    cin >> v;
    if(v == 1){
      cin >> x;
      pq.push(x);
    }else if(v == 2)cout << pq.top() << endl;
    else pq.pop();
  }
}
