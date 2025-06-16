#include <iostream>
#include <vector>
#include <set>

using namespace std;
using ll = long long;

set<ll> eratosthenes(ll num) {
    set<ll> prime;
    vector<bool> is_prime(num, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i <= num; i++) {
        if (is_prime[i]) {
            prime.insert(i);
            for (ll j = 2 * i; j <= num; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return prime;
}

int main(){
    int t;
    cin >> t;
    set<ll> primes = eratosthenes(1e7 + 1);
    while(t--){
        ll n;
        cin >> n;
        for(auto &p : primes){
            if(n == p*p*p)continue;
            if(primes.count(n / p*p)){
                cout << p << " " << n/(p*p) << endl;
                break;
            }
        }
    }
}
