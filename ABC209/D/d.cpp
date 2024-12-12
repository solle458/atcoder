#include <iostream>
#include <algorithm>
#include <vector>
#include <atcoder/segtree>

using namespace std;
using namespace atcoder;

int op(int a, int b){
  return min(a, b);
}

int e(){
  return 1e9;
}

int n;
vector<vector<int>> g;
vector<int> v, id;
segtree<int, op, e> seg(1e6);

void dfs(int now, int pre, int d){
  id[now] = v.size();
  seg.set(id[now], d);
  v.push_back(now);
  for(auto to : g[now]){
    if(to == pre)continue;
    dfs(to, now, d+1);
    seg.set(v.size(), d);
    v.push_back(now);
  }
}

int main(){
  int q;
  cin >> n >> q;
  g.resize(n);
  id.resize(n);
  for(int i = 0; i < n-1; i++){
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(0, -1, 0);
  for(int i = 0; i < q; i++){
    int u, v; 
    cin >> u >> v;
    u--;
    v--;
    int l = id[u], r = id[v];
    if(l > r)swap(l, r);
    int diff = seg.get(l)+seg.get(r)-2*seg.prod(l, r);
    if(diff%2 == 1)cout << "Road" << endl;
    else cout << "Town" << endl;
  }
}
