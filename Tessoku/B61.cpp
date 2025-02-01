#include <iostream>
#include <vector>
#include <algorithm>

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
    int fMax = -1, ans = 1e9;
    for(int i = 0; i < n; i++){
        if(int(a[i].size()) > fMax){
            fMax = a[i].size();
            ans = i;
        }
    }
    cout << ans+1 << endl;
}
