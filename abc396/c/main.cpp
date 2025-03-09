#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<long long> b(n), w(m);
    for(int i = 0; i < n; i++) cin >> b[i];
    for(int i = 0; i < m; i++) cin >> w[i];
    sort(b.rbegin(), b.rend());
    sort(w.rbegin(), w.rend());
    int i = 0, j = 0;
    long long ans = 0;
    while(1){
        vector<long long> tmp(3, -1e9);
        if(i < n and j < m and i >= j) tmp[0] = ans + b[i] + w[j];
        if(i < n) tmp[1] = ans + b[i];
        if(j < m and i > j) tmp[2] = ans + w[j];
        if(ans < tmp[0] and tmp[0] > tmp[1] && tmp[0] > tmp[2]){
            ans = tmp[0];
            i++;
            j++;
        }else if(ans < tmp[1] and tmp[1] > tmp[0] && tmp[1] > tmp[2]){
            ans = tmp[1];
            i++;
        }else if(ans < tmp[2] and tmp[2] > tmp[0] && tmp[2] > tmp[1]){
            ans = tmp[2];
            j++;
        }else{
            break;
        }
    }
    cerr << "i: " << i << " j: " << j << endl;
    cout << ans << endl;
}
