#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int n;
unordered_set<long long> ans;
unordered_map<string, bool> memo;

void solve(vector<long long> &a, int now){
    if(now == n){
        long long res = a[0];
        for(int i = 1; i < n; i++) res ^= a[i];
        ans.insert(res);
        return;
    }
    solve(a, now+1);
    string s = "";
    for(auto x : a) s += to_string(x) + ",";
    memo[s] = true;
    if(a[now] == 0)return;
    for(int i = now+1; i < n; i++){
        if(a[i] == 0)continue;
        long long tmpNow = a[now], tmpI = a[i];
        a[i] += a[now];
        a[now] = 0;
        string t = "";
        for(auto x : a) t += to_string(x) + ",";
        if(memo[t]){
            a[now] = tmpNow;
            a[i] = tmpI;
            continue;
        }
        solve(a, now+1);
        a[now] = tmpNow;
        a[i] = tmpI;
    }
}

int main(){
    cin >> n;
    vector<long long> a(n);
    for(auto &x: a) cin >> x;
    solve(a, 0);
    cout << ans.size() << endl;
}
