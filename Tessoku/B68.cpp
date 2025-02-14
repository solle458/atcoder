#include <iostream>
#include <vector>
#include <atcoder/maxflow>

using namespace std;
using namespace atcoder;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];

    mf_graph<int> mf(n + 2);

    int s = n, g = s + 1;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (p[i] >= 0) {
            mf.add_edge(s, i, p[i]);
            ans += p[i];
        } else
            mf.add_edge(i, g, -p[i]);
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        mf.add_edge(a, b, 1e9);
    }
    cout << (ans - mf.flow(s, g));
}
