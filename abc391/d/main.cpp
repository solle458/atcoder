#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main(){
    int n, w;
    cin >> n >> w;
    vector<pair<long long, long long>> yx(n);
    map<pair<long long, long long>, int> mp;
    int idx = 0;
    for(auto &[y, x] : yx){
        cin >> x >> y;
        mp[{y, x}] = idx++;
    }
    sort(yx.begin(), yx.end());
    vector<long long> ans(n+1, 1e18), lineMax(w+1, 0);
    vector<vector<long long>> ok(2e5);
    for(int i = 0; i < n; i++){
        long long x = yx[i].second, y = yx[i].first;
        if(lineMax[x] == 0){
            ok[1].push_back(mp[{y, x}]);
            lineMax[x] = 1;
            if(ok[1].size() == w){
                for(int j = 0; j < w; j++){
                    ans[ok[1][j]] = y;
                }
            }
        }else{
            long long h = lineMax[x] + 1;
            ok[h].push_back(mp[{y, x}]);
            lineMax[x] = h;
            if(ok[h].size() == w){
                for(int j = 0; j < w; j++){
                    ans[ok[h][j]] = y;
                }
            }
        }
    }
    for(int i = 2; i < 2e5; i++){
        if(ok[i].empty()) break;
        if(ans[ok[i].back()] <= ans[ok[i-1].back()]){
            for(int j = 0; j < ok[i].size(); j++){
                ans[ok[i][j]] = ans[ok[i-1].back()] + 1;
            }
        }
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        long long t, a;
        cin >> t >> a;
        if(ans[a-1] > t) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
}
