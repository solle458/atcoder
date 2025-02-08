#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct edge{
    int to, cost;
};

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<edge>> g(n);
    for(int i = 0; i < m; i++){
        int u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        g[u].push_back({v, c});
        g[v].push_back({u, c}); 
    }
    vector<int> dist(n, 1e9);
    dist[0] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0});
    while(!pq.empty()){
        auto [d, u] = pq.top();
        pq.pop();
        if(dist[u] < d)continue;
        for(auto [v, c] : g[u]){
            if(dist[v] > dist[u] + c){
                dist[v] = dist[u] + c;
                pq.push({dist[v], v});
            }
        }
    }
    vector<int> ans;
    ans.push_back(n-1);
    while(ans.back() != 0){
        for(auto [v, c] : g[ans.back()]){
            if(dist[v] + c == dist[ans.back()]){
                ans.push_back(v);
                break;
            }
        }
    }
    for(int i = ans.size()-1; i >= 0; i--)cout << ans[i]+1 << (i == 0 ? '\n' : ' ');
}
