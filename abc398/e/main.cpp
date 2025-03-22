#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

int dfs(int cnt, int goal, int v, vector<vector<int>> &g, vector<bool> &used){
    if(v == goal) return cnt;
    used[v] = true;
    int res = -1;
    for(int u : g[v]){
        if(used[u]) continue;
        res = dfs(cnt+1, goal, u, g, used);
        if(res != -1) return res;
    }
    return -1;
}

int main(){
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    set<pair<int, int>> tr;
    for(int i = 0; i < n-1; i++){
        int a, b;
        cin >> a >> b;
        a--; b--;
        tr.insert({min(a, b), max(a, b)});
        g[a].push_back(b);
        g[b].push_back(a);
    }
    set<pair<int, int>> s;
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(tr.count({i, j})) continue;
            vector<bool> used(n, false);
            int ch = dfs(1, j, i, g, used);
            if(ch%2 == 0) s.insert({min(i, j), max(i, j)});
        }
    }
    if(s.size()%2 == 0){
        cout << "Second" << endl;
        while(!s.empty()){
            int a, b;
            cin >> a >> b;
            if(a == -1 and b == -1) break;
            a--; b--;
            s.erase({min(a, b), max(a, b)});
            cout << s.begin()->first+1 << " " << s.begin()->second+1 << endl;
            s.erase(s.begin());
        }
    }else{
        cout << "First" << endl;
        while(!s.empty()){
            cout << s.begin()->first+1 << " " << s.begin()->second+1 << endl;
            s.erase(s.begin());
            int a, b;
            cin >> a >> b;
            if(a == -1 and b == -1) break;
            a--; b--;
            s.erase({min(a, b), max(a, b)});
        }
    }
}
