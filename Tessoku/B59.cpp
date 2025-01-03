#include <iostream>
#include <atcoder/segtree>

using namespace std;
using namespace atcoder;

int op(int a, int b){
  return a+b;
}

int e(){return 0;}

int main(){
  int n;
  cin >> n;
  segtree<int, op, e> seg(n);
  long long ans = 0;
  for(int i = 0; i < n; i++){
    int a;
    cin >> a;
    ans += seg.prod(a-1, n);
    seg.set(a-1, seg.get(a-1) + 1);
  }
  cout << ans << endl;
}
