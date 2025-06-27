#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<string> s(n);
    for(auto& si : s)cin >> si;
    vector<pair<int, int>> ans(n, {0, 0});
    for(int i = 0; i < n; i++){
        ans[i].second = i;
        for(int j = 0; j < n; j++)if(s[i][j] == 'o')ans[i].first++;
    }
    sort(ans.rbegin(), ans.rend(), [&](const pair<int, int>& a, const pair<int, int>& b){
        if(a.first == b.first)return a.second > b.second;
        return a.first < b.first;
    });
    for(int i = 0; i < n; i++){
        cout << ans[i].second + 1 << " ";
    }
    cout << endl;
}
