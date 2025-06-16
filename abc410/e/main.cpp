#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n, h, m;
    cin >> n >> h >> m;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++){
        cin >> a[i] >> b[i];
    }
    vector<pair<int, int>> now;
    now.push_back({h, m});
    int ans = 0;
    for(int i = 0; i < n; i++){
        vector<pair<int, int>> next;
        for(auto [hp, mp] : now){
            if(hp >= a[i]){
                next.push_back({hp - a[i], mp});
            }
            if(mp >= b[i]){
                next.push_back({hp, mp - b[i]});
            }
        }        
        if(next.empty()) break;
        sort(next.begin(), next.end(), greater<pair<int, int>>());
        vector<pair<int, int>> sorted;
        int max_mp = -1;
        for(auto [hp, mp] : next){
            if(mp > max_mp){
                sorted.push_back({hp, mp});
                max_mp = mp;
            }
        }
        now = sorted;
        ans = i + 1;
    }
    
    cout << ans << endl;
}
