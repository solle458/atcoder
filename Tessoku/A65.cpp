#include <iostream>
#include <vector>

using namespace std; 

int main(){
    int n;
    cin >> n;
    vector<vector<int>> a(n);
    for(int i = 1; i < n; i++){
        int p;
        cin >> p;
        a[p-1].push_back(i);
    }
    vector<int> memo(n, -1);
    auto dfs = [&](auto self, int v) -> int{
        if(memo[v] != -1)return memo[v];
        int res = a[v].size();
        for(auto x : a[v]) res += self(self, x);
        return memo[v] = res;
    };
    for(int i = 0; i < n; i++){
        int ans = a[i].size();
        for(auto x : a[i]){
            ans += dfs(dfs, x);
        }
        cout << ans << (i == n-1 ? '\n' : ' ');
    }
}
