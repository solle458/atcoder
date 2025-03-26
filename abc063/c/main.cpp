#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> s(n);
    for(auto &x : s)cin >> x;
    sort(s.rbegin(), s.rend());
    vector<vector<int>> dp(n+1, vector<int>(10001, 0));
    dp[0][0] = 1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 10001; j++){
            if(dp[i][j] == 1){
                dp[i+1][j] = 1;
                dp[i+1][j+s[i]] = 1;
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < 10001; i++)if(dp[n][i] == 1 && i % 10 != 0)ans = max(ans, i);
    cout << ans << endl;
}
