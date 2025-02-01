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
    for(int i = 0; i < n; i++){
        cout << i+1 << ": {";
        for(auto it = a[i].begin(); it != a[i].end(); ++it) cout << *it+1 << (it+1 == a[i].end() ? "" : ", ");
        cout << "}" << endl; 
    }
}
