#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for(auto &x : a) cin >> x;
    for(auto &x : b) cin >> x;
    sort(a.rbegin(), a.rend());
    sort(b.begin(), b.end());
    int ans = 0;
    for(int i = 0; i < n; i++)ans += a[i]*b[i];
    cout << ans << endl;
}
