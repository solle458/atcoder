#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    long long sum = 0, sumP = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
        sumP += a[i] * a[i];
    }
    long long ans = 0;
    ans += n * sumP - sum * sum;
    cout << ans << endl;
}
