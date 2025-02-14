#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m, x, y, z;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> dp(1 << n, 1e9);
    int c = 0;
    for (int i = 0; i < n; i++) c |= a[i] << i;
    dp[c] = 0;
    while (cin >> x >> y >> z) {
        x--;
        y--;
        z--;
        for (int j = 0; j < (1 << n); j++) {
            int k = j ^ (1 << x) ^ (1 << y) ^ (1 << z);
            dp[k] = min(dp[k], dp[j] + 1);
        }
    }
    int ans = dp[(1 << n) - 1];
    cout << (ans == 1000000000 ? -1 : ans) << '\n';
}
