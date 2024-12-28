#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main(){
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  iota(a.begin(), a.end(), 1);
  bool rev = false;
  for(int i = 0; i < q; i++){
    int v, x, y;
    cin >> v;
    if(v == 1){
      cin >> x >> y;
      x--;
      if(rev)a[n-1-x] = y;
      else a[x] = y;
    }else if(v == 2){
      rev ^= 1;
    }else{
      cin >> x;
      x--;
      if(rev)cout << a[n-1-x] << endl;
      else cout << a[x] << endl;
    }
  }
}

