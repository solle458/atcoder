#include <iostream>
#include <vector>
#include <algorithm>
#include <atcoder/dsu>

using namespace std;
using namespace atcoder;

int main(){
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m), c(m);
    for(int i = 0; i < m; i++){
        cin >> edges[i].first >> edges[i].second >> c[i].first;
        edges[i].first--;
        edges[i].second--;
        c[i].second = i;
    }
    sort(c.rbegin(), c.rend());
    dsu d(n);
    long long ans = 0;
    for(int i = 0; i < m; i++){
        if(d.same(edges[c[i].second].first, edges[c[i].second].second))continue;
        d.merge(edges[c[i].second].first, edges[c[i].second].second);
        ans += c[i].first;
    }
    cout << ans << endl;
}
