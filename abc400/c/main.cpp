#include <iostream>
#include <cmath>

using namespace std;

int main() {
    long long n;
    cin >> n;

    long long ans = 0, a = 1;
    while (true) {
        long long p = 1LL << a;
        if (p > n) break;

        long long max_bb = n / p;
        long long max_b = (long long) sqrtl(max_bb);
        ans += (max_b+1) / 2;
        a++;
    }

    cout << ans << endl;
    return 0;
}
