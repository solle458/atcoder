#include <iostream>
#include <vector>
#include <atcoder/maxflow>

using namespace std;
using namespace atcoder;

int main(){
    int n;
    cin >> n;
    vector<string> s(n);
    for(auto &x : s) cin >> x;
    mf_graph<int> g(2*n + 2);
    for(int i = 1; i <= n; i++){
        g.add_edge(0, i, 1);
        g.add_edge(n + i, 2*n + 1, 1);
    }
    for(int i = 0; i < n; i++)for(int j = 0; j < n; j++)if(s[i][j] == '#') g.add_edge(i + 1, n + j + 1, 1);
    cout << g.flow(0, 2*n + 1) << endl;
}
