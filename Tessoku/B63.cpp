#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

int main() {
    int h, w;
    pair<int, int> start, goal;
    cin >> h >> w >> start.first >> start.second >> goal.first >> goal.second;
    start.first--, start.second--, goal.first--, goal.second--;
    vector<string> s(h);
    for (int i = 0; i < h; i++) cin >> s[i];
    vector<vector<int>> dist(h, vector<int>(w, -1));
    queue<pair<int, int>> q;
    q.push(start);
    dist[start.first][start.second] = 0;
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 or nx >= h or ny < 0 or ny >= w) continue;
            if (s[nx][ny] == '#') continue;
            if (dist[nx][ny] != -1) continue;
            dist[nx][ny] = dist[x][y] + 1;
            q.push({nx, ny});
        }
    }
    cout << dist[goal.first][goal.second] << endl;
}
