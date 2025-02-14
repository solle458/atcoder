#include <iostream>
#include <algorithm>
#include <vector>
#include <atcoder/dsu>

using namespace std;
using namespace atcoder;

int main(){
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> g(m), c(m);
    for(int i = 0; i < m; i++){
        cin >> g[i].first >> g[i].second >> c[i].first;
        g[i].first--;
        g[i].second--;
        c[i].second = i;
    }
    sort(c.begin(), c.end());
    dsu d(n);
    long long ans = 0;
    for(int i = 0; i < m; i++){
        if(d.same(g[c[i].second].first, g[c[i].second].second)) continue;
        d.merge(g[c[i].second].first, g[c[i].second].second);
        ans += c[i].first;
    }
    cout << ans << endl;
}
