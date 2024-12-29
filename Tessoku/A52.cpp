#include <iostream>
#include <queue>

using namespace std;

int main(){
  int Q;
  cin >> Q;
  queue<string> que;
  for(int q = 0; q < Q; q++){
    int v;
    string x;
    cin >> v;
    if(v == 1){
      cin >> x;
      que.push(x);
    }else if(v == 2) cout << que.front() << endl;
    else que.pop();
  }
}
