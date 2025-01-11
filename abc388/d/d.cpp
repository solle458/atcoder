#include <iostream>
#include <atcoder/lazysegtree>

using namespace std;
using namespace atcoder;

struct S{
    int sum;
};

struct F{
    int add;
};

S op(S a, S b){
    return S{a.sum + b.sum};
}

S e(){
    return S{0};
}

S mapping(F f, S x){
    return S{x.sum + f.add};
}

F composition(F f, F g){
    return F{f.add + g.add};
}

F id(){
    return F{0};
}

int main(){
    int n;
    cin >> n;
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(n);
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        seg.set(i, S{a});
    }
    for(int i = 0; i < n; i++){
        int v = seg.get(i).sum, need = n-i-1;
        if(v >= need){
            int l = i+1, r = n;
            seg.apply(l, r, F{1});
            seg.set(i, S{v - need});
        }else{
            int l = i+1, r = i+1+v;
            seg.apply(l, r, F{1});
            seg.set(i, S{0});
        }
    }
    for(int i = 0; i < n; i++)cout << seg.get(i).sum << (i == n-1 ? "\n" : " ");
}
