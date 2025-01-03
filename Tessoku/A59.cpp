#include <iostream>
#include <atcoder/segtree>

using namespace std;
using namespace atcoder;

int op(int a, int b){
  return a+b;
}

int e(){return 0;}

int main(){
  int n, Q;
  cin >> n >> Q;
  segtree<int, op, e> seg(n);
  for(int q = 0; q < Q; q++){
    int v, pos, x, l, r;
    cin >> v;
    if(v == 1){
      cin >> pos >> x;
      seg.set(pos-1, x);
    }else{
      cin >> l >> r;
      cout << seg.prod(l-1, r-1) << endl;
    }
  }
}
