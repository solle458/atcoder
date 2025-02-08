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
        u--; v--;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    vector<bool> used(n, false);
    auto dfs = [&](auto self, int v) -> void{
        used[v] = true;
        for(int u : a[v]){
            if(used[u]) continue;
            self(self, u);
        }
    };
    dfs(dfs, 0);
    for(const auto &f : used)if(!f){
        cout << "The graph is not connected." << endl;
        return 0;
    }
    cout << "The graph is connected." << endl;
}
