#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        vector<int> ans(n, 0);
        vector<vector<int>> a(m, vector<int>(n));
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                cin >> a[i][j];
                ans[j] += a[i][j];
            }
        }
        sort(ans.rbegin(), ans.rend());
        cout << ans[0] << endl;
    }
}
