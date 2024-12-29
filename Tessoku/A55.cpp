#include <iostream>
#include <set>

using namespace std;

int main(){
  int Q;
  cin >> Q;
  set<int> s;
  for(int q = 0; q < Q; q++){
    int v, x;
    cin >> v >> x;
    if(v == 1)s.insert(x);
    else if(v == 2)s.erase(x);
    else{
      auto lb = s.lower_bound(x);
      if(lb == s.end())cout << -1 << endl;
      else cout << *lb << endl;
    }
  }
}
