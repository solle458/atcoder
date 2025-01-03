#include <iostream>
#include <algorithm>
#include <atcoder/segtree>

using namespace std;
using namespace atcoder;

int op(int a,int b){
    return min(a,b);
}

int e(){
    return 1<<30;
}

int main()
{
    int n;
    cin >> n;
    int l,r;
    cin >> l >> r;
    vector<int> x(n);
    for(int i=0;i<n;i++){
        cin >> x[i];
    }
    segtree<int,op,e> seg(n);
    seg.set(0,0);
    for(int i=1;i<n;i++){
        int left = lower_bound(x.begin(),x.end(),x[i]-r) -x.begin(); 
        int right = upper_bound(x.begin(),x.end(),x[i]-l) -x.begin(); 
        if(left==right)continue;
        seg.set(i,seg.prod(left,right)+1);
    }
    cout << seg.get(n-1) << endl;
    return 0;
}
