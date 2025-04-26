#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<vector<int>> calc_next(const string &s) {
    int n = (int)s.size();
    vector<vector<int>> res(n + 1, vector<int>(26, n));
    for (int i = n - 1; i >= 0; --i) {
        res[i] = res[i + 1];
        res[i][s[i] - 'a'] = i;
    }
    return res;
}

int main() {
    int n, k;
    string s;
    cin >> n >> k >> s;
    string res = "";
    auto nex = calc_next(s);
    int j = -1;
    for (int i = 0; i < k; ++i) {
        for (char c = 'a'; c <= 'z'; ++c) {
            int now = nex[j + 1][c - 'a'];
            if (n - now >= k - i) {
                res += c;
                j = now;
                break;
            }
        }
    }
    cout << res << endl;
}
