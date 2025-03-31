#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<tuple<int, double, int>>> g(n);
    for(int i = 0; i < m; i++){
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        a--; b--;
        if(d)g[a].push_back({b, (double)c-0.1, d});
        else g[a].push_back({b, c, d});
        if(d)g[b].push_back({a, (double)c-0.1, d});
        else g[b].push_back({a, c, d});
    }
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> que;
    vector<double> dist(n, 1e9);
    vector<bool> visited(n, false);
    dist[0] = 0.0;
    que.push({0.0, 0});
    while(!que.empty()){
        auto [c, v] = que.top();
        que.pop();
        if(visited[v]) continue;
        visited[v] = true;
        for(auto [u, w, nc] : g[v]){
            if(dist[u] > c+w){
                dist[u] = c+w;
                que.push({c+w, u});
            }
        }
    }
    int now = n-1, tree = 0;
    while(now != 0){
        for(auto [u, w, nc] : g[now]){
            if(dist[now] == dist[u]+w){
                now = u;
                if(nc)tree++;
                break;
            }
        }
    }
    cout << dist[n-1]+0.1*tree << " " << tree << endl;
}
