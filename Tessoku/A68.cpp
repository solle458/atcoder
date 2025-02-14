#include <iostream>
#include <atcoder/maxflow>

using namespace std;
using namespace atcoder;

int main(){
    int n, m;
    cin >> n >> m;
    mf_graph<int> g(n);
    for(int i = 0; i < m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        g.add_edge(a-1, b-1, c);
    }
    cout << g.flow(0, n-1) << endl;
}
