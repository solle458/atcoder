#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n;
    long long a, b;
    cin >> n >> a >> b;
    vector<long long> h(n);
    for(auto &x : h) cin >> x;
    long long l = 0, r = 1e9;
    while(r-l > 1){
        long long mid = (l+r)/2;
        long long cnt = 0;
        for(auto &x : h){
            long long hp = x - mid*b;
            if(hp > 0) cnt += (hp + a - b - 1) / (a - b);
        }
        if(cnt <= mid) r = mid;
        else l = mid;
    }
    cout << r << endl;
}
