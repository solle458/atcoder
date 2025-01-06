#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(){
  int n, sum = 0;
  cin >> n;
  sum = n;
  vector<int> a(n);
  map<int, int> mp;
  for(int i = 0; i < n; i++){
    cin >> a[i];
    mp[a[i]]++;
  }
  long long ans = 0;
  for(int i = 0; i < n; i++){
    mp[a[i]]--;
    sum--;
    ans += sum-mp[a[i]];
  }
  cout << ans << endl;
}
