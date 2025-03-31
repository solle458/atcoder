#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n, x;
    cin >> n >> x;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i] >> b[i];
    vector<vector<bool>> dp(n+1, vector<bool>(x+1, false));
    dp[0][0] = true;
    for(int i = 0; i < n; i++){
        for(int j = 0; j <=x; j++){
            if(!dp[i][j]) continue;
            if(j+a[i] <= x) dp[i+1][j+a[i]] = true;
            if(j+b[i] <= x) dp[i+1][j+b[i]] = true;
        }
    }
    cout << (dp[n][x] ? "Yes" : "No") << endl;
}
