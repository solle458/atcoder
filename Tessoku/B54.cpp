#include <iostream>
#include <map>

using namespace std;

int main(){
  int n;
  cin >> n;
  map<int, int> mp;
  for(int i = 0; i < n; i++){
    int a;
    cin >> a;
    mp[a]++;
  }
  long long ans = 0;
  for(auto [f, s] : mp){
    for(int i = 0; i < s; i++){
      mp[f]--;
      ans += mp[f];
    }
  }
  cout << ans << endl;
}
