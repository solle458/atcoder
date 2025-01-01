#include <iostream>
#include <vector>

using namespace std;

int main(){
  int n, Q;
  cin >> n >> Q;
  vector<int> a(n);
  vector<vector<int>> dp(30, vector<int>(n, 0));
  for(auto &x : a)cin >> x;
  for(int i = 0; i < n; i++)dp[0][i] = a[i]-1;
  for(int i = 1; i < 30; i++)for(int j = 0; j < n; j++)dp[i][j] = dp[i-1][dp[i-1][j]];
  for(int q = 0; q < Q; q++){
    long long x, y;
    cin >> x >> y;
    long long pos = x-1;
    for(int i = 29; i >= 0; i--)if((y / (1<<i)) % 2 != 0)pos = dp[i][pos];
    cout << pos+1 << endl;
  }
}
