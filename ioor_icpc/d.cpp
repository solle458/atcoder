#include <algorithm>
#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    long long a, l;
    while (cin >> a >> l) {
        if (a == 0 and l == 0) break;
        int idx = 1;
        map<long long, int> s;
        s[a] = 1;
        while (true) {
            string s1 = to_string(a);
            if (s1.size() != l) s1 = string(l - s1.size(), '0') + s1;
            sort(s1.begin(), s1.end());
            long long min = stoll(s1);
            sort(s1.rbegin(), s1.rend());
            long long max = stoll(s1);
            long long ans = max - min;
            if (s.count(ans)){
                cout << s[ans]-1 << " " << ans << " " << idx-s[ans]+1 << endl;
                break;
            }
            idx++;
            s[ans] = idx;
            a = ans;
        }
    }
}
