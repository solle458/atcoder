#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m), ans;
    for(auto &x : a) cin >> x;
    for(auto &x : b) cin >> x;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for(int i = 0; i < m; i++){
        long long cntA = upper_bound(a.begin(), a.end(), b[i]) - a.begin();
        long long cntB = upper_bound(a.begin(), a.end(), b[i] + 1) - a.begin();
        if(cntA >= i+1){
            ans.push_back(b[i]);
        }
        if(cntB >= i+1){
            ans.push_back(b[i] + 1);
        }
    }
    for(int i = 0; i < n; i++){
        long long cntA = upper_bound(b.begin(), b.end(), a[i]) - b.begin();
        long long cntB = upper_bound(b.begin(), b.end(), a[i] + 1) - b.begin();
        if(cntA <= i+1){
            ans.push_back(a[i]);
        }
        if(cntB <= i+1){
            ans.push_back(a[i] + 1);
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans[0] << endl;
}
