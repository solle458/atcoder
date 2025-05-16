#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    int q;
    long long l;
    cin >> l >> q;
    set<int> s;
    s.insert(0);
    s.insert(l);
    for(int i = 0; i < q; i++) {
        int c, x;
        cin >> c >> x;
        if(c == 1) {
            s.insert(x);
        } else {
            auto it = s.upper_bound(x);
            cout << *it - *prev(it) << endl;
        }
    }
}
