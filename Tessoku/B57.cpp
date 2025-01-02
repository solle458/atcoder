#include <iostream>
#include <vector>

using namespace std;

int main(){
  int n, k;
  cin >> n >> k;
  vector<vector<int>> dp(30, vector<int>(n+1, 0));
  for(int i = 1; i <= n; i++){
    string s = to_string(i);
    dp[0][i] = i;
    for(int j = 0; j < s.size(); j++) dp[0][i] -= (int)(s[j]-'0');
  }
  for(int i = 1; i < 30; i++)for(int j = 1; j <= n; j++) dp[i][j] = dp[i-1][dp[i-1][j]];
  for(int i = 1; i <= n; i++){
    int pos = i;
    for(int j = 29; j >= 0; j--)if(k & (1<<j)) pos = dp[j][pos];
    cout << pos << endl;
  }
}
