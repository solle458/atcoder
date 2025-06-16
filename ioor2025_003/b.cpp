#include <iostream>
#include <deque>

using namespace std;

int main() {
    int n;
    cin >> n;
    deque<long long> h(n);
    for(int i = 0; i < n; i++) {
        cin >> h[i];
    }
    long long prev = h.back();
    h.pop_back();
    while(!h.empty()) {
        long long x = h.back();
        h.pop_back();
        if(x-1 > prev) {
            cout << "No" << endl;
            return 0;
        }
        if(x == prev or x-1 == prev) {
            continue;
        }
        prev = min(prev, x);
    }
    cout << "Yes" << endl;
}
