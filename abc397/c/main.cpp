#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    map<int, int> pre, suf;
    for(auto &x : a){
        cin >> x;
        suf[x]++;
    }
    int ans = 0;
    for(int i = 0; i < n; i++){
        int x = a[i];
        pre[x]++;
        suf[x]--;
        if(suf[x] == 0) suf.erase(x);
        ans = max(ans, int(suf.size() + pre.size()));
    }
    cout << ans << endl;
}
