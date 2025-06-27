#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<long long> a(n);
    for(auto& ai : a)cin >> ai;
    sort(a.begin(), a.end());
    long long ans = 0;
    for(int i = 0; i < n; i++){
        auto lb = lower_bound(a.begin(), a.end(), a[i]*2) - a.begin();
        ans += n - lb;
    }
    cout << ans << endl;
}
