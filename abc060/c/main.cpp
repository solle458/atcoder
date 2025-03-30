#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int n, t;
    cin >> n >> t;
    vector<int> a(n);
    for(auto &x : a)cin >> x;
    long long ans = t;
    for(int i = 1; i < n; i++)ans += min(t, a[i]-a[i-1]);
    cout << ans << endl;
}
