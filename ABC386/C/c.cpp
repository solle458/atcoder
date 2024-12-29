#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
  int k;
  string s, t;
  cin >> k >> s >> t;
  int sl = s.size(), tl = t.size();
  if(abs(sl-tl) > k){
    cout << "No" << endl;
    return 0;
  }
  vector<vector<int>> dp(sl+1, vector<int>(2*k + 1, 1e9));
  dp[0][k] = 0;
  for(int i = 0; i <= sl; i++){
    for(int dj = 0; dj <= 2*k; dj++){
      int j = i+dj-k;
      if(j < 0)continue;
      if(j > tl)continue;
      if(i > 0 and dj < 2*k)dp[i][dj] = min(dp[i][dj], dp[i-1][dj+1]+1);
      if(j > 0 and dj > 0)dp[i][dj] = min(dp[i][dj], dp[i][dj-1]+1);
      if(i > 0 and j > 0){
        int add = 1;
        if(s[i-1] == t[j-1])add = 0;
        dp[i][dj] = min(dp[i][dj], dp[i-1][dj]+add);
      }
    }
  }
  if(dp[sl][k+tl-sl] <= k)cout << "Yes" << endl;
  else cout << "No" << endl;
}
