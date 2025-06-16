#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge{
    int to;
    long long cost;
};

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> g(n);
    for(int i = 0; i < m; i++){
        int a, b;
        long long c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].push_back({b, c});
    }
    vector<vector<bool>> dist(n, vector<bool>(1024, false));
    queue<pair<int, int>> q;
    q.push({0, 0});
    dist[0][0] = true;
    while(!q.empty()){
        int cost = q.front().first;
        int v = q.front().second;
        q.pop();
        for(auto e : g[v]){
            int new_cost = cost ^ e.cost;
            if(!dist[e.to][new_cost]){
                dist[e.to][new_cost] = true;
                q.push({new_cost, e.to});
            }
        }
    }
    for(int i = 0; i < 1024; i++){
        if(dist[n-1][i]){
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;
}
