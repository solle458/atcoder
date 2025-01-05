#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<long long> a(9), b(9);
    for(auto &x : a) cin >> x;
    for(auto &x : b) cin >> x;
    long long ans = 0;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            ans += a[i] * b[j];
        }
    }
    cout << ans << endl;
}
