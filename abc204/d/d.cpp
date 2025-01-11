#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n, sum = 0;
    cin >> n;
    vector<int> a(n);
    for(auto &x : a){
        cin >> x;
        sum += x;
    }
    vector<vector<bool>> dp(n+1, vector<bool>(sum+1, false));
    dp[0][0] = true;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < sum+1; j++){
            dp[i+1][j] = dp[i][j];
            if(j >= a[i])dp[i+1][j] = dp[i+1][j] || dp[i][j-a[i]];
        }
    }
    int ans = -1, mn = 1e9, mid = ((sum%2 == 0) ? sum/2 : sum/2+1);
    for(int i = 0; i < sum+1; i++)if(dp[n][i]){
        ans = (mn != min(mn, abs(mid-i))) ? i : ans;
        mn = min(mn, mid-i);
    }
    cout << max(ans, sum-ans) << endl;
}
