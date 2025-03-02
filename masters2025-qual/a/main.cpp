#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <map>

using namespace std;

// 方向情報
const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
const string dir[] = {"U", "L", "D", "R"};
const map<string, string> rev = {{"U", "D"}, {"D", "U"}, {"L", "R"}, {"R", "L"}};

// 探索開始位置（プレイヤーの位置）
pair<int, int> player_pos{-1, -1};

// スコア計算関数
long long GetScore(int t) {
    return round(1e6 * (1 + log2(10000 / t)));
}

// BFSでプレイヤーの移動経路を探索する
vector<string> find_path_bfs(int n, vector<string> &grid, pair<int, int> hole, pair<int, int> ore, char label) {
    vector<vector<int>> dist(n, vector<int>(n, -1));
    queue<pair<int, int>> q;

    // プレイヤーの位置から探索開始
    q.push(player_pos);
    dist[player_pos.first][player_pos.second] = 0;

    // BFS 探索
    while (!q.empty()) {
        auto [y, x] = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if (grid[ny][nx] != '.' && grid[ny][nx] != label) continue;
            if (dist[ny][nx] != -1) continue;
            dist[ny][nx] = dist[y][x] + 1;
            q.push({ny, nx});
        }
    }

    // 鉱石までの最短距離を計算
    dist[ore.first][ore.second] = 1e9;
    for (int i = 0; i < 4; i++) {
        int nx = ore.second + dx[i], ny = ore.first + dy[i];
        if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
        if (dist[ny][nx] != -1) dist[ore.first][ore.second] = min(dist[ny][nx] + 1, dist[ore.first][ore.second]);
    }

    if (dist[ore.first][ore.second] == 1e9) return {}; // 到達不可能なら空リストを返す

    // 経路復元（プレイヤー → 鉱石）
    deque<string> move_to_ore;
    pair<int, int> cur = ore;
    while (cur != player_pos) {
        for (int i = 0; i < 4; i++) {
            int nx = cur.second + dx[i], ny = cur.first + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if (dist[ny][nx] == -1) continue;
            if (dist[ny][nx] == dist[cur.first][cur.second] - 1) {
                move_to_ore.push_front("1 " + dir[i]);
                cur = {ny, nx};
                break;
            }
        }
    }

    // プレイヤー位置を更新
    player_pos = ore;

    // 再度 BFS（鉱石 → 穴）
    q = queue<pair<int, int>>();
    q.push(player_pos);
    dist = vector<vector<int>>(n, vector<int>(n, -1));
    dist[player_pos.first][player_pos.second] = 0;

    while (!q.empty()) {
        auto [y, x] = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if (grid[ny][nx] != '.' && grid[ny][nx] != label) continue;
            if (dist[ny][nx] != -1) continue;
            dist[ny][nx] = dist[y][x] + 1;
            q.push({ny, nx});
        }
    }

    // 穴までの最短距離を計算
    dist[hole.first][hole.second] = 1e9;
    for (int i = 0; i < 4; i++) {
        int nx = hole.second + dx[i], ny = hole.first + dy[i];
        if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
        if (dist[ny][nx] != -1) dist[hole.first][hole.second] = min(dist[ny][nx] + 1, dist[hole.first][hole.second]);
    }

    if (dist[hole.first][hole.second] == 1e9) return {}; // 到達不可能なら空リストを返す

    // 経路復元（鉱石 → 穴）
    deque<string> move_to_hole;
    cur = hole;
    while (cur != player_pos) {
        for (int i = 0; i < 4; i++) {
            int nx = cur.second + dx[i], ny = cur.first + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            if (dist[ny][nx] == -1) continue;
            if (dist[ny][nx] == dist[cur.first][cur.second] - 1) {
                move_to_hole.push_front("2 " + dir[i]);
                cur = {ny, nx};
                break;
            }
        }
    }

    player_pos = hole;

    // 結果をまとめて返す
    vector<string> ans;
    ans.insert(ans.end(), move_to_ore.begin(), move_to_ore.end());
    ans.insert(ans.end(), move_to_hole.begin(), move_to_hole.end());
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    vector<pair<int, int>> ores;
    map<pair<int, int>, char> ore_to_hole_map;
    pair<int, int> holeA, holeB, holeC;

    // 入力処理
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        for (int j = 0; j < n; j++) {
            if (grid[i][j] >= 'a' && grid[i][j] <= 'z') {
                ores.push_back({i, j});
                ore_to_hole_map[{i, j}] = toupper(grid[i][j]); // 対応する穴を保存
            }
            if (grid[i][j] == 'A') holeA = {i, j};
            if (grid[i][j] == 'B') holeB = {i, j};
            if (grid[i][j] == 'C') holeC = {i, j};
        }
    }

    player_pos = holeA; // 初期位置を設定
    vector<string> ans;
    vector<pair<int, int>> miss;
    for (auto &ore : ores) {
        char label;
        pair<int, int> hole;
        if(ore_to_hole_map[ore] == 'A'){
            hole = holeA;
            label = 'A';
        }
        if(ore_to_hole_map[ore] == 'B'){
            hole = holeB;
            label = 'B';
        }
        if(ore_to_hole_map[ore] == 'C'){
            hole = holeC;
            label = 'C';
        }
        auto path = find_path_bfs(n, grid, hole, ore, label);
        if (path.empty()) {
            miss.push_back(ore);
            continue;
        }
        ans.insert(ans.end(), path.begin(), path.end());
        grid[ore.first][ore.second] = '.'; // 鉱石を回収
    }

    for(auto &ore : miss){
        char label;
        pair<int, int> hole;
        if(ore_to_hole_map[ore] == 'A'){
            hole = holeA;
            label = 'A';
        }
        if(ore_to_hole_map[ore] == 'B'){
            hole = holeB;
            label = 'B';
        }
        if(ore_to_hole_map[ore] == 'C'){
            hole = holeC;
            label = 'C';
        }
        auto path = find_path_bfs(n, grid, hole, ore, label);
        if (path.empty()) continue;
        ans.insert(ans.end(), path.begin(), path.end());
        grid[ore.first][ore.second] = '.'; // 鉱石を回収
    }

    for (int i = 0; i < min(10000-1, int(ans.size())); i++) cout << ans[i] << endl;
}
