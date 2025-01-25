#include <iostream>
#include <vector>
#include <algorithm>
#include <atcoder/lazysegtree>

using namespace std;
using namespace atcoder;

int op(int a, int b){
    return a+b;
}

int e(){
    return 0;
}

int mapping(int a, int b){
    return a+b;
}

int composition(int a, int b){
    return a+b;
}

int id(){
    return 0;
}

int main(){
    int n;
    cin >> n;
    lazy_segtree<int, op, e, int, mapping, composition, id> seg(1e6);
    
}
