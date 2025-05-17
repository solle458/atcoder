#include <iostream>
#include <vector>

using namespace std;

int digit(long long x){
    int d = 0;
    while(x > 0){
        d++;
        x /= 10;
    }
    return d;
}

int main(){
    int n, k;
    cin >> n >> k;
    long long ans = 1;
    vector<long long> a(n);
    for(auto &x : a) cin >> x;
    for(int i = 0; i < n; i++){
        if(digit(ans) + digit(a[i]) - 1 > k) ans = 1;
        else ans *= a[i];
        if(digit(ans) > k) ans = 1;
    }
    cout << ans << endl;
}
