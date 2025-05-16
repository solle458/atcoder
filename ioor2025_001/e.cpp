#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n; cin >> n;
    vector<pair<int,int>> v(n);
    for(int i = 0; i < n; i++) cin >> v[i].first >> v[i].second;
    sort(v.begin(), v.end());
    int ans = 0;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++){
        if(v[i].first < v[j].first && v[i].second < v[j].second) {
            pair<int,int> p1 = {v[i].first, v[j].second}, p2 = {v[j].first, v[i].second};
            if(binary_search(v.begin(), v.end(), p1) && binary_search(v.begin(), v.end(), p2)) ans++;
        }
    }
    cout << ans << endl;
}
