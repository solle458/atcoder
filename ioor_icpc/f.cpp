#include <iostream>
#include <bitset>
#include <unordered_map>
#include <sstream>

using namespace std;
const int BSZ = 110;

bitset<BSZ> R;
unordered_map<string, bool> M;

string mkKey(int k, int tot, int L, int r, const bitset<BSZ>& d) {
    ostringstream oss;
    oss << k << "_" << tot << "_" << L << "_" << r << "_" << d.to_string();
    return oss.str();
}

bool dfs(int k, int tot, int L, int r, const bitset<BSZ>& d) {
    if ((d & R) == R) {
        if (r >= L * (tot - k)) return true;
    }
    if (k == tot) return (r == 0 && ((d & R) == R));
    string key = mkKey(k, tot, L, r, d);
    if (M.count(key)) return M[key];
    int left = tot - k;
    int maxVal = r / left;
    for (int x = L; x <= maxVal; x++) {
        bitset<BSZ> nd = d | (d << x);
        if (dfs(k + 1, tot, x, r - x, nd)) {
            M[key] = true;
            return true;
        }
    }
    M[key] = false;
    return false;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    while (true) {
        int n;
        cin >> n;
        if (n == 0) break;
        string s;
        cin >> s;
        R.reset();
        for (int i = 0; i <= n; i++) R.set(i, s[i] == 'o');

        int ans = 0;
        for (int tot = 1; tot <= n; tot++){
            M.clear();
            bitset<BSZ> d;
            d.reset();
            d.set(0, true);
            if (dfs(0, tot, 1, n, d)) {
                ans = tot;
                break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}

