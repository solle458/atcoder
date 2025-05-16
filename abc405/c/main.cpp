#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<long long> a(n), sum(n+1, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum[i+1] = sum[i] + a[i];
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans += a[i]*(sum[n]-sum[i+1]);
    }
    cout << ans << endl;
}
