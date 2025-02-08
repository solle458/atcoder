#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <atcoder/dsu>

using namespace std;
using namespace atcoder;

int main() {
    int n, m;
    cin >> n >> m;
    dsu d(n);
    vector<set<int>> g(n);
    vector<pair<int, int>> p;
    map<pair<int, int>, int> idx;
    set<pair<int, int>> s;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].insert(b);
        g[b].insert(a);
        if (a == b) p.push_back({i + 1, a});
        else if (s.count({a, b}) or s.count({b, a})) p.push_back({i + 1, a});
        s.insert({a, b});
        s.insert({b, a});
        d.merge(a, b);
        idx[{a, b}] = i + 1;
        idx[{b, a}] = i + 1;
    }
    vector<bool> visited(n, false);
    vector<bool> edge(m + 1, false);
    auto dfs = [&](auto self, int v, int parent) -> void {
        visited[v] = true;
        for (auto u : g[v]) {
            if (u == parent) continue;
            int edgeIdx = idx[{v, u}];
            if (visited[u]) {
                if (!edge[edgeIdx]) {
                    p.push_back({edgeIdx, v});
                    edge[edgeIdx] = true;
                }
            } else {
                self(self, u, v);
            }
        }
    };
    for (int i = 0; i < n; i++) if (!visited[i]) dfs(dfs, i, -1);
    vector<vector<int>> groups = d.groups();
    vector<pair<pair<int, int>, int>> ans;
    for (auto [i, v] : p) {
        for (const auto& group : groups) {
            if (d.same(v, group[0])) continue; 
            ans.emplace_back(make_pair(i, v), group[0]);
            d.merge(v, group[0]);
            break;
        }
    }
    cout << ans.size() << endl;
    for (auto [p, q] : ans) {
        cout << p.first << " " << p.second + 1 << " " << q + 1 << endl;
    }
}
