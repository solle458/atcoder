#include <iostream>
#include <vector>
#include <atcoder/modint>

using namespace std;
using namespace atcoder;

using mint = modint998244353;

struct Comb {
    vector<mint> fact, ifact;

    Comb(int n) {
        fact.resize(n + 1);
        ifact.resize(n + 1);

        fact[0] = 1;
        for (int i = 1; i <= n; i++) {
            fact[i] = fact[i - 1] * i;
        }

        ifact[n] = fact[n].inv();
        for (int i = n; i >= 1; i--) {
            ifact[i - 1] = ifact[i] * i;
        }
    }

    mint comb(int n, int k) {
        if (k < 0 || k > n) return 0;
        return fact[n] * ifact[k] * ifact[n - k];
    }
};


int main() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    int n = a + b + c + d;

    Comb comb(n);

    mint ans;

    for(int i = 0; i <= c; i++){
        ans += comb.comb(a+b+i, b)*comb.comb(d-1+c-i, d-1);
    }

    cout << ans.val() << endl;
}

