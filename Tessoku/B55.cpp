#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

int main(){
  int Q;
  cin >> Q;
  set<int> s;
  for(int q = 0; q < Q; q++){
    int v, x;
    cin >> v >> x;
    if(v == 1)s.insert(x);
    else{
      if(s.empty()){
        cout << -1 << endl;
        continue;
      }
      auto lb = s.lower_bound(x);
      if(lb == s.end())cout << abs(x-*prev(lb)) << endl;
      else if(lb == s.begin())cout << abs(x-*lb) << endl;
      else cout << min(abs(x-*lb), abs(x-*prev(lb))) << endl;
    }
  }
}
