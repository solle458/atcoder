#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    vector<int> ans;
    vector<bool> used(n, false);
    const auto dfs = [&](auto &&f, int v) -> void{
        if(used[n-1])return;
        used[v] = true;
        ans.push_back(v);
        for(int u : a[v]){
            if(used[u])continue;
            f(f, u);
        }
        if(!used[n-1]){
            ans.pop_back();
            used[v] = false;
        }
    };
    dfs(dfs, 0);
    for(auto x : ans) cout << x+1 << " ";
    cout << endl;
}
