#include <iostream>
#include <vector>
#include <set>

using namespace std;

const long long mod = 1e9 + 7;

int main(){
    long long n, m;
    cin >> n >> m;
    set<int> s;
    for(int i = 0; i < m; i++){
        int a;
        cin >> a;
        s.insert(a);
    }
    vector<long long> dp(n + 1, 0);
    dp[0] = 1;
    for(int i = 1; i <= n; i++){
        if(s.find(i) != s.end()) continue;
        if(i == 1) dp[i] = dp[i - 1];
        else dp[i] = (dp[i - 1] + dp[i - 2]) % mod;
    }
    cout << dp[n] << endl;
}
