#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

int merge(int dp_cum, int d){
    return max(dp_cum, d);
}

int add_root(int d){
    return d + 1;
}

int dfs(int v, int p, vector<vector<int>>& g, vector<int>& dp){
    int deg = g[v].size();
    if(deg == 1)return dp[v] = 0;
    int dp_cum = 0;
    for(int u : g[v]){
        if(u == p)continue;
        dp_cum = merge(dp_cum, dfs(u, v, g, dp));
    }
    return dp[v] = add_root(dp_cum);
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int> dp(n, -1);
    dfs(0, -1, g, dp);
    cout << dp[0] << endl;
    return 0;
}
