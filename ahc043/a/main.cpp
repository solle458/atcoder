#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
#include <atcoder/dsu>

using namespace std;
using namespace atcoder;

const int EMPTY = -1;
const int DO_NOTHING = -1;
const int STATION = 0;
const int RAIL_HORIZONTAL = 1;
const int RAIL_VERTICAL = 2;
const int RAIL_LEFT_DOWN = 3;
const int RAIL_LEFT_UP = 4;
const int RAIL_RIGHT_UP = 5;
const int RAIL_RIGHT_DOWN = 6;
const int COST_STATION = 5000;
const int COST_RAIL = 100;
const int dr[] = {0, 1, 0, -1}, dc[] = {1, 0, -1, 0};

class Person {
    public:
    pair<int, int> home, workplace;
    vector<vector<int>> field, dis;
    Person() : home({0, 0}), workplace({0, 0}) {}
    Person(pair<int, int> home, pair<int, int> workplace) : home(home), workplace(workplace) {}

    void bfs(vector<vector<int>>& Field){
        field = Field;
        dis = vector<vector<int>>(field.size(), vector<int>(field[0].size(), 1e9));
        queue<pair<int, int>> que;
        que.push(home);
        dis[home.first][home.second] = 0;
        while(!que.empty()){
            auto [r, c] = que.front();
            que.pop();
            for(int i = 0; i < 4; i++){
                int nr = r + dr[i], nc = c + dc[i];
                if(nr < 0 || nr >= field.size() || nc < 0 || nc >= field[0].size()) continue;
                if(field[nr][nc] != EMPTY) continue;
                if(dis[nr][nc] != 1e9) continue;
                dis[nr][nc] = dis[r][c] + 1;
                que.push({nr, nc});
            }
        }
    }
    vector<pair<int, int>> shortestPath(){
        vector<pair<int, int>> ans;
        int r = workplace.first, c = workplace.second;
        while(r != home.first || c != home.second){
            ans.push_back({r, c});
            for(int i = 0; i < 4; i++){
                int nr = r + dr[i], nc = c + dc[i];
                if(nr < 0 || nr >= field.size() || nc < 0 || nc >= field[0].size()) continue;
                if(dis[nr][nc] != dis[r][c] - 1) continue;
                r = nr, c = nc;
                break;
            }
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
    int calcCost(vector<pair<int, int>>& path){
        return (path.size()-2) * COST_RAIL + 2 * COST_STATION;
    }
};

int main(){
    int n, m, k, t;
    cin >> n >> m >> k >> t;
    vector<Person> people(m);
    for(int i = 0; i < m; i++){
        int r, c, r2, c2;
        cin >> r >> c >> r2 >> c2;
        people[i] = Person({r, c}, {r2, c2});
    }
    vector<int> cost(m);
    vector<vector<int>> field(n, vector<int>(n, EMPTY));
    vector<vector<pair<int, int>>> path(m);
    for(int i = 0; i < m; i++){
        people[i].bfs(field);
        path[i] = people[i].shortestPath();
        cost[i] = people[i].calcCost(path[i]);
    }
}
