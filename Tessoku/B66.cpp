#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <atcoder/dsu>

using namespace std;
using namespace atcoder;

int main(){
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> id(n);
    map<pair<int, int>, bool> used;
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--; b--;
        pair<int, int> p = {min(a, b), max(a, b)};
        id[i] = p;
        used[p] = false;
    }
    dsu d(n);
    int Q;
    cin >> Q;
    vector<pair<int, int>> query(Q);
    for(int i = 0; i < Q; i++){
        int q, x, u, v;
        cin >> q;
        if(q == 1){
            cin >> x;
            used[id[x-1]] = true;
            query[i] = {x-1, -1};
        }else{
            cin >> u >> v;
            query[i] = {u-1, v-1};
        }
    }
    for(auto p : used)if(!p.second) d.merge(p.first.first, p.first.second);
    vector<string> ans;
    for(int i = Q-1; i >= 0; i--){
        if(query[i].second == -1) d.merge(id[query[i].first].first, id[query[i].first].second);
        else ans.push_back(d.same(query[i].first, query[i].second) ? "Yes" : "No");
    }
    reverse(ans.begin(), ans.end());
    for(auto s : ans) cout << s << endl;
}
