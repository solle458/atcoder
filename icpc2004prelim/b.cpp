#include <iostream>
#include <vector>

using namespace std;

int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};

void dfs(vector<string> &s, int h, int w, pair<int, int> now){
    int x = now.second, y = now.first;
    for(int i = 0; i < 4; i++){
        int nx = dx[i]+x, ny = dy[i]+y;
        if(0 > ny or ny >= h or 0 > nx or nx >= w)continue;
        if(s[ny][nx] != '.')continue;
        s[ny][nx] = ',';
        dfs(s, h, w, {ny, nx});
    }
}

int main(){
    int h, w;
    while(cin >> w >> h, (h != 0 and w != 0)){
        pair<int, int> start;
        vector<string> s(h);
        for(int i = 0; i < h; i++){
            cin >> s[i];
            for(int j = 0; j < w; j++)if(s[i][j] == '@'){
                start = {i, j};
                s[i][j] = ',';
            }
        }
        dfs(s, h, w, start);
        int ans = 0;
        for(int i = 0; i < h; i++)for(int j = 0; j < w; j++)if(s[i][j] == ',')ans++;
        cout << ans << endl;
    }
}
