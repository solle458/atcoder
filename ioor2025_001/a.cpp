#include <iostream>

using namespace std;

int main(){
    long long n, a, b;
    cin >> n >> a >> b;
    long long tmp = a+b;
    long long ans = n/tmp * a;
    ans += min(n%tmp, a);
    cout << ans << endl;
}
