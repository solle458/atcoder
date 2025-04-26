#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> k(m), b(n);
    vector<vector<int>> a(m);
    for(int i = 0; i < m; i++){
        cin >> k[i];
        a[i].resize(k[i]);
        for(auto &x : a[i]) cin >> x;
    }
    for(auto &x : b)cin >> x;
    map<int, int> idx;
    for(int i = 0; i < n; i++) idx[b[i]] = i;
    vector<int> maxs(m, -1);
    for(int i = 0; i < m; i++){
        for(auto &x : a[i]){
            if(idx[x] > maxs[i]) maxs[i] = idx[x];
        }
    }
    vector<int> ans(n+1, 0);
    for(auto &x : maxs) ans[x]++;
    for(int i = 0; i < n; i++){
        ans[i+1] += ans[i];
        cout << ans[i] << endl;
    }
}
