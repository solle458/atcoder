#include <iostream>
#include <vector>
using namespace std;

int main(){
    long long n, l;
    cin >> n >> l;
    vector<long long> a(n-1), circle(l, 0);
    for(auto &i : a)cin >> i;
    if(l%3 != 0){
        cout << 0 << endl;
        return 0;
    }
    long long pre = 0;
    circle[0] = 1;
    for(int i = 0; i < n-1; i++){
        circle[(a[i]+pre)%l] += 1;
        pre = (a[i]+pre)%l;
    }
    long long s = l/3, t = (l*2)/3, ans = 0;
    for(int i = 0; i < l/3; i++){
        ans += circle[i] * circle[i+s] * circle[i+t];
    }
    cout << ans << endl;
}
