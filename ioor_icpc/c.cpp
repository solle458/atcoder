#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main() {
    int n, m, p;
    while (cin >> m >> n >> p) {
        if (n == 0 && m == 0 && p == 0) break;
        vector<bool> vis(m, false);
        vis[p-1] = true;
        for (int i = 0; i < n; i++) {
            int a, b;
            cin >> a >> b;
            if(vis[a-1] or vis[b-1]){
                vis[a-1] = true;
                vis[b-1] = true;
            }
        }
        int ans = 0;
        for(int i = 0; i < m; i++) if(vis[i]) ans++;
        cout << ans << endl;
    }
}
