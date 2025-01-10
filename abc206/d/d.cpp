#include <iostream>
#include <vector>
#include <algorithm>
#include <atcoder/dsu>

using namespace std;
using namespace atcoder;

int main(){
  int n;
  cin >> n;
  vector<int> a(n);
  for(auto &x : a){
    cin >> x;
    x--;
  }
  dsu d(2*100000);
  for(int i = 0; i < n/2; i++){
    if(a[i] != a[n-i-1]){
      d.merge(a[i], a[n-i-1]);
    }
  }
  int ans = 0;
  for(int i = 0; i < 2*100000; i++)if(i == d.leader(i)) ans += d.size(i) - 1;
  cout << ans << endl;
}
