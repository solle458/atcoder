#include <iostream>
#include <vector>
#include <algorithm>
#include <atcoder/modint>

using namespace std;
using mint = atcoder::modint998244353;

string to_binary(long long n) {
    string res;
    while (n) {
        res += (n % 2) + '0';
        n /= 2;
    }
    reverse(res.begin(), res.end());
    return res;
}

pair<mint, mint> dfs(int pos, int cnt, bool smaller, const string &b, int k,
                     vector<vector<vector<pair<bool, pair<mint, mint>>>>> &memo) {
    if (cnt > k) return {0, 0};
    if (pos == b.size()) return cnt == k ? make_pair(1, 0) : make_pair(0, 0);

    if (memo[pos][cnt][smaller].first) return memo[pos][cnt][smaller].second;

    int lim = smaller ? b[pos] - '0' : 1;
    mint cntN = 0, sumN = 0;

    for (int d = 0; d <= lim; ++d) {
        bool new_smaller = smaller && (d == lim);
        auto [sub_count, sub_sum] = dfs(pos + 1, cnt + d, new_smaller, b, k, memo);
        int rem = b.size() - pos - 1;
        mint add = mint(d) * mint(1LL << rem) * sub_count;
        cntN += sub_count;
        sumN += sub_sum + add;
    }

    memo[pos][cnt][smaller] = {true, {cntN, sumN}};
    return {cntN, sumN};
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long n;
        int k;
        cin >> n >> k;

        string b = to_binary(n);
        int l = b.size();

        vector<vector<vector<pair<bool, pair<mint, mint>>>>> memo(
            l + 1, vector<vector<pair<bool, pair<mint, mint>>>>(k + 2, vector<pair<bool, pair<mint, mint>>>(2, {false, {0, 0}}))
        );

        mint ans = dfs(0, 0, true, b, k, memo).second;
        cout << ans.val() << '\n';
    }
}
