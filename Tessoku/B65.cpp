#include <iostream>
#include <vector>
#include <algorithm>

using namespace std; 

int main(){
    int n, t;
    cin >> n >> t; 
    vector<vector<int>> a(n);
    for(int i = 1; i < n; i++){
        int u, v;
        cin >> u >> v;
        u--;v--;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    vector<int> memo(n, -1);
    auto dfs = [&](auto self, int v, int p) -> int{
        if(memo[v] != -1)return memo[v];
        int res = 0;
        for(auto x : a[v])if(x != p)res = max(res, self(self, x, v)+1);
        return memo[v] = res;
    };
    for(auto x : a[t-1]) memo[t-1] = max(memo[t-1], dfs(dfs, x, t-1)+1);
    for(auto ans : memo) cout << ans << ' ';
    cout << endl;
}
