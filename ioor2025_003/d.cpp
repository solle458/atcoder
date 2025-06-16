#include <iostream>
#include <vector>
#include <cmath>
#include <atcoder/modint>

using namespace std;
using mint = atcoder::modint998244353;

int digit(long long n){
    int d = 0;
    while(n > 0){
        d++;
        n /= 10;
    }
    return d;
}

mint sum(long long n, long long d){
    mint ans = 0;
    for(int i = d+1; i <= n; i++){
        ans += i;
    }
    return ans;
}

int main() {
    long long n;
    cin >> n;
    mint ans = 0;
    for(int i = 1; i < digit(n); i++){
        ans += 9 * powl(10, (i - 1));
        cerr << 9 * powl(10, (i - 1)) << endl;
    }
    long long d = 1;
    for(int i = 0; i < digit(n); i++) d *= 10;
    d--;
    n -= d;
    ans += sum(n, d);
    cout << ans.val() << endl;
}
