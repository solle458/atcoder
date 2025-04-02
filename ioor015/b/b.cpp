#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(m), b(m);
    for(int i = 0; i < m; i++) cin >> a[i] >> b[i];
    vector<vector<int>> g(n);
    for(int i = 0; i < m; i++) g[b[i]-1].push_back(a[i]-1);
    int cnt = 0, ans = -1;
    for(int i = 0; i < n; i++){
        if(g[i].size() == 0){
            cnt++;
            ans = i;
        }
    }
    if(cnt == 1) cout << ans+1 << endl;
    else cout << -1 << endl;
}
