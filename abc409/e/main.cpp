#include <iostream>
#include <vector>

using namespace std;

vector<vector<pair<int, long long>>> adj;
vector<long long> x;
long long total_cost = 0;

long long dfs(int v, int parent) {
    long long flow = x[v];
    for (auto &edge : adj[v]) {
        int next = edge.first;
        long long weight = edge.second;
        if (next == parent) continue;
        long long child_flow = dfs(next, v);
        flow += child_flow;
        total_cost += abs(child_flow) * weight;
    }
    return flow;
}

int main() {
    int n;
    cin >> n;
    adj.resize(n + 1);
    x.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    dfs(1, -1);
    cout << total_cost << endl;
}
