#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, long long>>> g(n);
    for(int i = 0; i < m; i++){
        int u, v;
        long long c;
        cin >> u >> v >> c;
        u--; v--;
        g[u].push_back({v, c});
        g[v].push_back({u, c});
    };
    long long ans = 9e18;
    vector<bool> visited(n, false);
    function<void(int, long long)> dfs = [&](int p, long long sum){
        if(p == n-1){
            ans = min(ans, sum);
            return;
        }
        visited[p] = true;
        for(auto [to, cost] : g[p]){
            if(visited[to]) continue;
            dfs(to, sum ^ cost);
        }
        visited[p] = false;
    };
    dfs(0, 0);
    cout << (ans == 9e18 ? -1 : ans) << endl;
}
