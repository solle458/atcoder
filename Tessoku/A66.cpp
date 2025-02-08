#include <iostream>
#include <atcoder/dsu>

using namespace std;
using namespace atcoder;

int main(){
    int n, Q;
    cin >> n >> Q;
    dsu d(n);
    while(Q--){
        int q, u, v;
        cin >> q >> u >> v;
        u--; v--;
        if(q == 1) d.merge(u, v);
        else cout << (d.same(u, v) ? "Yes" : "No") << endl;
    }
}
