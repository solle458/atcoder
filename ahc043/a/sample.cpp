#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cassert>

using namespace std;

using Pos = pair<int, int>;

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

class UnionFind {
public:
    int n;
    vector<int> parents;

    UnionFind(int n) : n(n), parents(n * n, -1) {}

    int find_root(int idx) {
        if (parents[idx] < 0) return idx;
        return parents[idx] = find_root(parents[idx]);
    }

    bool is_same(Pos p, Pos q) {
        int p_idx = p.first * n + p.second;
        int q_idx = q.first * n + q.second;
        return find_root(p_idx) == find_root(q_idx);
    }

    void unite(Pos p, Pos q) {
        int p_idx = p.first * n + p.second;
        int q_idx = q.first * n + q.second;
        int p_root = find_root(p_idx);
        int q_root = find_root(q_idx);

        if (p_root != q_root) {
            if (-parents[p_root] > -parents[q_root]) swap(p_root, q_root);
            parents[q_root] += parents[p_root];
            parents[p_root] = q_root;
        }
    }
};

int distance(Pos a, Pos b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

class Action {
public:
    int type;
    Pos pos;

    Action(int type, Pos pos) : type(type), pos(pos) {}

    void print() const {
        if (type == DO_NOTHING) cout << "-1\n";
        else cout << type << " " << pos.first << " " << pos.second << "\n";
    }
};

class Field {
public:
    int N;
    vector<vector<int>> rail;
    UnionFind uf;

    Field(int N) : N(N), rail(N, vector<int>(N, EMPTY)), uf(N) {}

    void build(int type, int r, int c) {
        assert(rail[r][c] != STATION);
        if (1 <= type && type <= 6) assert(rail[r][c] == EMPTY);
        rail[r][c] = type;

        // 上下左右の接続
        if (type == STATION || type == RAIL_VERTICAL || type == RAIL_LEFT_UP || type == RAIL_RIGHT_UP) {
            if (r > 0 && (rail[r - 1][c] == STATION || rail[r - 1][c] == RAIL_VERTICAL || rail[r - 1][c] == RAIL_LEFT_DOWN || rail[r - 1][c] == RAIL_RIGHT_DOWN))
                uf.unite({r, c}, {r - 1, c});
        }
        if (type == STATION || type == RAIL_VERTICAL || type == RAIL_LEFT_DOWN || type == RAIL_RIGHT_DOWN) {
            if (r < N - 1 && (rail[r + 1][c] == STATION || rail[r + 1][c] == RAIL_VERTICAL || rail[r + 1][c] == RAIL_LEFT_UP || rail[r + 1][c] == RAIL_RIGHT_UP))
                uf.unite({r, c}, {r + 1, c});
        }
        if (type == STATION || type == RAIL_HORIZONTAL || type == RAIL_LEFT_DOWN || type == RAIL_LEFT_UP) {
            if (c > 0 && (rail[r][c - 1] == STATION || rail[r][c - 1] == RAIL_HORIZONTAL || rail[r][c - 1] == RAIL_RIGHT_DOWN || rail[r][c - 1] == RAIL_RIGHT_UP))
                uf.unite({r, c}, {r, c - 1});
        }
        if (type == STATION || type == RAIL_HORIZONTAL || type == RAIL_RIGHT_DOWN || type == RAIL_RIGHT_UP) {
            if (c < N - 1 && (rail[r][c + 1] == STATION || rail[r][c + 1] == RAIL_HORIZONTAL || rail[r][c + 1] == RAIL_LEFT_DOWN || rail[r][c + 1] == RAIL_LEFT_UP))
                uf.unite({r, c}, {r, c + 1});
        }
    }
};

class Solver {
public:
    int N, M, K, T;
    vector<Pos> home, workplace;
    Field field;
    int money;
    vector<Action> actions;

    Solver(int N, int M, int K, int T, vector<Pos>& home, vector<Pos>& workplace)
        : N(N), M(M), K(K), T(T), home(home), workplace(workplace), field(N), money(K) {}

    int calc_income() {
        int income = 0;
        for (int i = 0; i < M; i++) {
            if (field.uf.is_same(home[i], workplace[i])) {
                income += distance(home[i], workplace[i]);
            }
        }
        return income;
    }

    void build_rail(int type, int r, int c) {
        field.build(type, r, c);
        money -= COST_RAIL;
        actions.emplace_back(type, Pos(r, c));
    }

    void build_station(int r, int c) {
        field.build(STATION, r, c);
        money -= COST_STATION;
        actions.emplace_back(STATION, Pos(r, c));
    }

    void build_nothing() {
        actions.emplace_back(DO_NOTHING, Pos(0, 0));
    }

    void solve() {
        int rail_count = (K - COST_STATION * 2) / COST_RAIL;
        int person_idx = 0;

        while (person_idx < M) {
            if (distance(home[person_idx], workplace[person_idx]) - 1 <= rail_count) break;
            person_idx++;
        }

        assert(person_idx != M);
        build_station(home[person_idx].first, home[person_idx].second);
        build_station(workplace[person_idx].first, workplace[person_idx].second);

        int r0 = home[person_idx].first, c0 = home[person_idx].second;
        int r1 = workplace[person_idx].first, c1 = workplace[person_idx].second;

        for (int r = min(r0, r1) + 1; r < max(r0, r1); r++) build_rail(RAIL_VERTICAL, r, c0);
        for (int c = min(c0, c1) + 1; c < max(c0, c1); c++) build_rail(RAIL_HORIZONTAL, r1, c);

        money += calc_income();
        while (actions.size() < T) {
            build_nothing();
            money += calc_income();
        }

        for (const auto& action : actions) action.print();
        cerr << "score=" << money << endl;
    }
};

int main() {
    int N, M, K, T;
    cin >> N >> M >> K >> T;
    vector<Pos> home(M), workplace(M);
    for (int i = 0; i < M; i++) {
        cin >> home[i].first >> home[i].second >> workplace[i].first >> workplace[i].second;
    }

    Solver solver(N, M, K, T, home, workplace);
    solver.solve();
    return 0;
}
