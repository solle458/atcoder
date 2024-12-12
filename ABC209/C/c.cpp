#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int mod = 1e9+7;

int main(){
  int n;
  cin >> n;
  vector<long long> c(n), dp(n, 0);
  for(auto &x : c)cin >> x;
  sort(c.begin(), c.end());
  dp[0] = c[0];
  for(int i = 1; i < n; i++){
    if(c[i] < i+1){
      cout << 0 << endl;
      return 0;
    }
    dp[i] = ((c[i]-i)*dp[i-1])%mod;
  }
  cout << dp[n-1] << endl;
}
