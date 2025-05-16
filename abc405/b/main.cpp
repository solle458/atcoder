#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for(auto &x : a) cin >> x;
    int ans = -1;
    bool ok = true;
    while(ok){
        ans++;
        vector<bool> used(m, false);
        for(auto &x : a){
            used[x-1] = true;
        }
        for(int i = 0; i < m; i++){
            if(!used[i]){
                ok = false;
                break;
            }
        }
        a.pop_back();
    }
    cout << ans << endl;
}
