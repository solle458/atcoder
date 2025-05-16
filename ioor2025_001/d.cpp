#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, w;
    cin >> n >> w;
    vector<long long> s(n), t(n), p(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> t[i] >> p[i];
    }
    vector<long long> sum(200001, 0);
    for (int i = 0; i < n; i++) {
        sum[s[i]] += p[i];
        sum[t[i]] -= p[i];
    }
    for (int i = 1; i < 200001; i++) {
        sum[i] += sum[i - 1];
    }
    for (int i = 0; i < 200001; i++) {
        if (sum[i] > w) {
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
}
