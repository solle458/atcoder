#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main(){
    long long n, k;
    cin >> n >> k;
    map<long long, long long> mp;
    for(int i = 0; i < n; i++){
        long long a, b;
        cin >> a >> b;
        mp[a] += b;
    }
    int idx = 0;
    vector<long long> sum(mp.size()+1, 0);
    map<long long, long long> mp2;
    for(auto [k, v] : mp){
        sum[idx+1] = sum[idx] + v;
        idx++;
        mp2[idx] = k;
    }
    auto lb = lower_bound(sum.begin(), sum.end(), k);
    cout << mp2[lb - sum.begin()] << endl;
}
