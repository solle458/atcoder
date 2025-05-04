#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs(int v, int s, vector<vector<int>> &a, vector<bool> &used){
    used[v] = true;
    if(a[v].size() != 2)return;
    for(auto u : a[v]){
        if(!used[u]){
            dfs(u, s, a, used);
        }
    }
}

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
    if(m != n){
        cout << "No" << endl;
        return 0;
    }
    vector<bool> used(n, false);
    dfs(0, 0, a, used);
    for(auto u : used){
        if(!u){
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
}
