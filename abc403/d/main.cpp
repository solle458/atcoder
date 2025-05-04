#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

template <class T>
bool chmin(T &a, T b) {
    if (a > b) {
        a = b;
        return true;
    } else {
        return false;
    }
}

int main() {
    int n, d;
    cin >> n >> d;
    vector<long long> a(n);
    map<long long, int> mp;
    for(auto& x : a){
        cin >> x;
        mp[x]++;
    }
    vector<long long> dp(n);
    for(int i = 0; i < n; i++)dp[i] = i;
    for(int i = 0; i < n-1; i++){
        if(abs(a[i]-a[i+1])!=d)dp[i+1] = min(dp[i+1], dp[i]);
    }
    for(auto x : dp) cout << x << " ";
    cout << endl;
    cout << dp[n-1] << endl;
}
