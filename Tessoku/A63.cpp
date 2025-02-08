#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> dist(n, -1);
    dist[0] = 0;
    vector<vector<int>> g(n);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    queue<int> q;
    q.push(0);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v : g[u]){
            if(dist[v] == -1){
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    for(auto x : dist) cout << x << endl;
}
