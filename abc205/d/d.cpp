#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n, Q;
    cin >> n >> Q; 
    vector<long long> a(n);
    for(auto &x : a)cin >> x;
    sort(a.begin(), a.end());
    for(int q = 0; q < Q; q++){
        long long k;
        cin >> k;
        long long l = 0, r = 2e18;
        while(r-l > 1){
            long long mid = (r+l)/2;
            auto lb = lower_bound(a.begin(), a.end(), mid);
            long long idx;
            if(lb == a.end()) idx = n;
            else idx = lb - a.begin();
            if(mid - idx == k){
                if(mid == *lb){
                  r--;
                  continue;
                }
                cout << mid << endl;
                break;
            }else if(mid - idx > k) r = mid + 1;
            else l = mid;
        }
    }
}