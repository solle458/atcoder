#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

int main() {
    int h, w;
    cin >> h >> w;

    vector<string> grid(h);
    vector<vector<int>> dist(h, vector<int>(w, -1));
    vector<string> ans_grid(h);

    queue<pair<int, int>> q;

    for (int i = 0; i < h; ++i) {
        cin >> grid[i];
        ans_grid[i] = grid[i];
        for (int j = 0; j < w; ++j) {
            if (grid[i][j] == 'E') {
                q.push({i, j});
                dist[i][j] = 0;
            }
        }
    }

    const int dy[] = {-1, 1, 0, 0};
    const int dx[] = {0, 0, -1, 1};
    const char arrow[] = {'v', '^', '>', '<'};

    while (!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();
        int y = p.first;
        int x = p.second;

        for (int i = 0; i < 4; ++i) {
            int ny = y + dy[i];
            int nx = x + dx[i];

            if (ny < 0 or ny >= h or nx < 0 or nx >= w) continue;
            if (grid[ny][nx] == '#') continue;

            if (dist[ny][nx] != -1) continue;
            dist[ny][nx] = dist[y][x] + 1;
            ans_grid[ny][nx] = arrow[i];
            q.push({ny, nx});
        }
    }

    for (int i = 0; i < h; ++i) {
        cout << ans_grid[i] << endl;
    }
}
