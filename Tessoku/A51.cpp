#include <iostream>
#include <stack>

using namespace std;

int main(){
  stack<string> s;
  int Q;
  cin >> Q;
  for(int q = 0; q < Q; q++){
    int v;
    string x;
    cin >> v;
    if(v == 1){
      cin >> x;
      s.push(x);
    }else if(v == 2)cout << s.top() << endl;
    else s.pop();
  }
}
