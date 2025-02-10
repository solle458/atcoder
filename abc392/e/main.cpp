#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#include <atcoder/dsu>

using namespace std;
using namespace atcoder;

int main() {
    int n, m;
    cin >> n >> m;
    dsu d(n);
    vector<int> cycle;
    vector<pair<int, int>> edge(m);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        edge[i] = {a, b};
        if(d.same(a, b)) cycle.push_back(i);
        d.merge(a, b);
    }
    vector<vector<int>> groups = d.groups();
    set<int> leaders;
    for(auto &g : groups) leaders.insert(d.leader(g[0]));
    vector<tuple<int, int, int>> ans;
    for(auto &c : cycle) {
        for(auto &l : leaders) {
            if(d.same(edge[c].first, l)) continue;
            ans.push_back({c+1, edge[c].second+1, l+1});
            d.merge(edge[c].first, l);
            leaders.erase(l);
            break;
        }
    }
    cout << ans.size() << endl;
    for(auto &a : ans) cout << get<0>(a) << " " << get<1>(a) << " " << get<2>(a) << endl;
}
