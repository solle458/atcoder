#include <iostream>
#include <queue>

using namespace std;

int main(){
  int n, x;
  string s;
  cin >> n >> x >> s;
  x--;
  queue<int> q;
  q.push(x);
  s[x] = '@';
  while(!q.empty()){
    int now = q.front();
    q.pop();
    if(now-1 >= 0 and s[now-1] == '.'){
      s[now-1] = '@';
      q.push(now-1);
    }
    if(now+1 < n and s[now+1] == '.'){
      s[now+1] = '@';
      q.push(now+1);
    }
  }
  cout << s << endl;
}
