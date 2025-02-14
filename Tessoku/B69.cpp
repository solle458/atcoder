#include <iostream>
#include <vector>
#include <atcoder/maxflow>

using namespace std;
using namespace atcoder;

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];
    mf_graph<int> g(n + 24 + 2);
    for (int i = 0; i < n; i++) g.add_edge(n + 24, i, 10);
    for (int i = 0; i < n; i++)for (int j = 0; j < 24; j++)if (c[i][j] == '1') g.add_edge(i, n + j, 1);
    for (int j = 0; j < 24; j++) g.add_edge(n + j, n + 25, m);
    if (g.flow(n + 24, n + 25) == m * 24) cout << "Yes" << '\n';
    else cout << "No" << '\n';
}
