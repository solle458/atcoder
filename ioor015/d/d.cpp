#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
long long ans = 0;

void dfs(int v, int p, long long sum, vector<vector<pair<int, long long>>> &g, vector<bool> &visited){
    ans = max(ans, sum);
    visited[v] = true;
    for(auto [u, c] : g[v]){
        if(visited[u]) continue;
        dfs(u, p+1, sum+c, g, visited);
    }
    visited[v] = false;
}

int main() {
    cin >> n >> m;
    vector<vector<pair<int, long long>>> g(n);
    for(int i = 0; i < m; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    for(int i = 0; i < n; i++){
        vector<bool> visited(n, false);
        dfs(i, 0, 0, g, visited);
    }
    cout << ans << endl;
}
