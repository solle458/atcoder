#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

const int dx[] = {0, 1}, dy[] = {1, 0};
int h, w;
long long ans = 0;

void dfs(set<int> &memo, vector<vector<int>> &a, int y, int x){
    if(x == w-1 and y == h-1){
        ans++;
        return;
    }
    for(int i = 0; i < 2; i++){
        int nx = x + dx[i], ny = y + dy[i];
        if(nx < 0 or ny < 0 or nx >= w || ny >= h)continue;
        if(memo.count(a[ny][nx]))continue;
        memo.insert(a[ny][nx]);
        dfs(memo, a, ny, nx);
        memo.erase(a[ny][nx]);
    }
}

int main(){
    cin >> h >> w;
    vector<vector<int>> a(h, vector<int>(w));
    for(int i = 0; i < h; i++)for(int j = 0; j < w; j++)cin >> a[i][j];
    set<int> memo;
    memo.insert(a[0][0]);
    dfs(memo, a, 0, 0);
    cout << ans << endl;
}
