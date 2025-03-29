#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    int T;
    cin >> T;
    for(int t = 0; t < T; t++) {
        int n;
        cin >> n;
        vector<int> a(2 * n);
        vector<bool> b(2 * n, false);
        map<int, vector<int>> m;

        for (int i = 0; i < 2 * n; i++) {
            cin >> a[i];
            a[i]--;
            m[a[i]].push_back(i);
        }
        for (int i = 0; i < 2 * n - 1; i++) {
            if (a[i] == a[i + 1]) b[a[i]] = true;
        }
        long long ans = 0;
        for (auto &[k, v] : m) {
            if (b[k]) continue;
            int left1 = v[0] - 1, right1 = v[0] + 1;
            int left2 = v[1] - 1, right2 = v[1] + 1;
            if (left1 >= 0 and right2 < 2 * n and a[left1] >= k and a[right2] >= k and a[left1] == a[right2] and left1 != right2) ans++;
            if (right1 < 2 * n and left2 >= 0 and a[left2] >= k and a[right1] >= k and a[right1] == a[left2] and right1 != left2) ans++;
            if (left1 >= 0 and left2 >= 0 and a[left1] >= k and a[left2] >= k and a[left1] == a[left2] and left1 != left2) ans++;
            if (right1 < 2 * n and right2 < 2 * n and a[right1] >= k and a[right2] >= k and a[right1] == a[right2] and right1 != right2) ans++;
        }
        cout << ans << endl;
    }
}
