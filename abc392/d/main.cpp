#include <iostream>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

int main() {
    int n;
    cin >> n;
    long double ans = 0;
    vector<int> k(n);
    vector<map<long double, int>> cnt(n);
    for (int i = 0; i < n; i++) {
        cin >> k[i];
        for (int j = 0; j < k[i]; j++) {
            long double x;
            cin >> x;
            cnt[i][x]++;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            long double tmp = 0;
            int si = k[i], sj = k[j];
            auto it1 = cnt[i].begin();
            auto it2 = cnt[j].begin();
            while (it1 != cnt[i].end() && it2 != cnt[j].end()) {
                if (it1->first == it2->first) {
                    long double p1 = it1->second / (long double)si;
                    long double p2 = it2->second / (long double)sj;
                    tmp += p1 * p2;
                    ++it1;
                    ++it2;
                } else if (it1->first < it2->first) {
                    ++it1;
                } else {
                    ++it2;
                }
            }
            ans = max(ans, tmp);
        }
    }
    cout << fixed << setprecision(20) << ans << endl;
}
