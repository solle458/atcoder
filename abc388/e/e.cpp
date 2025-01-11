#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<long long> a(n);
    for(auto &x : a) cin >> x;
    int l = 0, r = n;
    while(r-l > 1){
        int mid = (l+r)/2, tmp = n-mid;
        if(mid * 2 > n){
            r = mid;
            continue;
        }
        bool ok = true;
        for(int i = 0; i < mid; i++)if(a[i]*2 > a[tmp+i]) ok = false;
        if(ok) l = mid;
        else r = mid; 
    }
    cout << l << endl;
}
