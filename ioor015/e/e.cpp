#include <iostream>
#include <vector>
#include <atcoder/lazysegtree>

using namespace std;
using namespace atcoder;

int op(int a, int b) {
    return a+b;
}

int e() {
    return 0;
}

int mapping(int f, int x) {
    return f+x;
}

int composition(int f, int g) {
    return f+g;
}

int id() {
    return 0;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    lazy_segtree<int, op, e, int, mapping, composition, id> seg(a);
    for(int i = 0; i < n; i++) seg.set(i, a[i]);
    for(int i = 0; i < n; i++){
        int x = seg.get(i);
        if(x >= n-1-i){
            seg.apply(i+1, n, 1);
            seg.set(i, x-(n-1-i));
        }else{
            seg.apply(i+1, i+x+1, 1);
            seg.set(i, 0);
        }
    }
    for(int i = 0; i < n; i++) cout << seg.get(i) << " ";
    cout << endl;
}
