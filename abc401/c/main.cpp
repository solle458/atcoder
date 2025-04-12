#include <iostream>
#include <vector>

using namespace std;

const long long MOD = 1e9;

int main(){
    long long n, k;
    cin >> n >> k;
    vector<long long> ans(n+1, 0), sum(n+1, 0);
    ans[0] = 1;
    sum[0] = 1;
    for(int i = 1; i <= n; i++){
        if(i < k) ans[i] = 1;
        else if(i == k) ans[i] = sum[i-1];
        else ans[i] = ((sum[i-1] - sum[i-k-1]) % MOD + MOD) % MOD;
        sum[i] = (sum[i-1] + ans[i]) % MOD;
    }
    cout << ans[n] << endl;
}
