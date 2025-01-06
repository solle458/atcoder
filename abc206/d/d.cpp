#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main(){
  int n;
  cin >> n;
  vector<int> a(n);
  for(auto &x : a) cin >> x;
  map<int, int> l, r;
  for(int i = 0; i < n/2; i++){
    if(a[i] != a[n-1-i]){
      l[a[i]]++;
      r[a[n-1-i]]++;
    }
  }
  bool eq = false;
  for(auto [f, s] : l){
    if(r.count(f))eq = true;
  }
  if(l.empty())cout << 0 << endl;
  else if(eq) cout << max(l.size())-1 << endl;
  else cout << max(l.size(), r.size()) << endl;
}
