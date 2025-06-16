#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    long long n;
    cin >> n;
    vector<long long> a(n);
    for(int i = 0; i < n; i++)cin >> a[i];
    sort(a.rbegin(), a.rend());
    long long ans = -1;
    for(int i = 100; i >= 0; i--){
        long long cnt = 0;
        for(int j = 0; j < n; j++){
            if(a[j] >= i)cnt++;
        }
        if(cnt >= i){
            ans = i;
            break;
        }
    }
    cout << (ans == -1 ? 0 : ans) << endl;
}
