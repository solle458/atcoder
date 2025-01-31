#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    long long n, m;
    string s, t;
    cin >> n >> m >> s >> t;
    long long now = 0;
    vector<pair<char, long long>> id(m);
    for(long long i = 0; i < m; i++) id[i] = {t[i], i};
    sort(id.rbegin(), id.rend());
    vector<bool> used(m, false);
    for(long long i = 0; i < m; i++){
        while (now < n and s[now] >= id[i].first) now++;
        if(now == n) break;
        s[now] = id[i].first;
        used[id[i].second] = true;
        now++;
    }
    if(!used[m-1]){
        for(long long i = 0; i < n; i++){
            if(s[i] <= t[m-1]){
                s[i] = t[m-1];
                used[m-1] = true;
                break;
            }
        }
    }
    if(!used[m-1]) s[n-1] = t[m-1];
    cout << s << endl;
}
