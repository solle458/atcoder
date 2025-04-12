#include <iostream>
#include <vector>
#include <deque>

using namespace std;

const int INF = 1e9;
int h, w;
vector<string> s;
int a, b, c, d;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

int main(){
    cin >> h >> w;
    s.resize(h);
    for(auto& row : s) cin >> row;
    cin >> a >> b >> c >> d;
    a--; b--; c--; d--;

    vector<vector<int>> dist(h, vector<int>(w, INF));
    deque<pair<int, int>> dq;
    dist[a][b] = 0;
    dq.push_front({a, b});

    while(!dq.empty()){
        auto [x, y] = dq.front(); dq.pop_front();
        for(int dir = 0; dir < 4; ++dir){
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if(0 <= nx && nx < h && 0 <= ny && ny < w && s[nx][ny] == '.'){
                if(dist[nx][ny] > dist[x][y]){
                    dist[nx][ny] = dist[x][y];
                    dq.push_front({nx, ny});
                }
            }

            int wx1 = x + dx[dir];
            int wy1 = y + dy[dir];
            int wx2 = x + 2*dx[dir];
            int wy2 = y + 2*dy[dir];
            if(0 <= wx1 && wx1 < h && 0 <= wy1 && wy1 < w && s[wx1][wy1] == '#'){
                if(dist[wx1][wy1] > dist[x][y] + 1){
                    dist[wx1][wy1] = dist[x][y] + 1;
                    dq.push_back({wx1, wy1});
                }
            }
            if(0 <= wx2 && wx2 < h && 0 <= wy2 && wy2 < w && s[wx1][wy1] == '#' && (s[wx2][wy2] == '#' || s[wx2][wy2] == '.')){
                if(dist[wx2][wy2] > dist[x][y] + 1){
                    dist[wx2][wy2] = dist[x][y] + 1;
                    dq.push_back({wx2, wy2});
                }
            }
        }
    }

    if (dist[c][d] == INF) cout << -1 << endl;
    else cout << dist[c][d] << endl;

    return 0;
}
