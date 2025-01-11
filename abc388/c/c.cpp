#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x : a) cin >> x;
    long long ans = 0;
    for(auto x : a){
        auto lb = lower_bound(a.begin(), a.end(), x*2);
        ans += a.end() - lb;
    }
    cout << ans << endl;
}
