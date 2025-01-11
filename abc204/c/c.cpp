#include <iostream>
#include <vector>

using namespace std;

void dfs(int now, vector<vector<int>> &g, vector<bool> &visited){
    visited[now] = true;
    for(int next : g[now]){
        if(visited[next])continue;
        dfs(next, g, visited);
    }
}

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
    }
    int ans = 0;
    for(int i = 0; i < n; i++){
        vector<bool> visited(n, false);
        dfs(i, g, visited);
        int cnt = 0;
        for(bool v : visited)if(v) cnt++;
        ans += cnt;
    }
    cout << ans << endl;
}
