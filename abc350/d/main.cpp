#include <iostream>
#include <vector>
#include <map>
#include <atcoder/dsu>

using namespace std;
using namespace atcoder;

int main(){
    int n, m;
    cin >> n >> m;
    dsu d(n);
    vector<int> a(n), b(n), cnt(n), edge(n);
    for(int i = 0; i < m; i++){
        cin >> a[i] >> b[i];
        a[i]--; b[i]--;
        d.merge(a[i], b[i]);
    }
    for(int i = 0; i < n; i++)cnt[d.leader(i)]++;
    for(int i = 0; i < m; i++)edge[d.leader(a[i])]++;
    long long ans = 0;
    for(int i = 0; i < n; i++){
        if(d.leader(i) != i)continue;
        ans += cnt[i] * (cnt[i] - 1) / 2 - edge[i];
    }
    cout << ans << endl;
}
