#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int countDemon(vector<string> &board, int n) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // cout << board[i][j] << (j == n - 1 ? '\n' : ' ');
            if (board[i][j] == 'x') res++;
        }
    }
    return res;
}

int main() {
    int n;
    cin >> n;
    vector<string> board(n);
    for (auto &s : board) cin >> s;
    int demon = countDemon(board, n);
    while (demon) {
        pair<char, int> best;
        int bestScore = 1e9;
        for (int i = 0; i < n; i++) {
            vector<pair<int, char>> score;
            if (board[i][0] != 'o') {
                score.push_back({0, 'L'});
                if (board[i][0] == 'x') score.back().first = -1;
                for (int j = 1; j < n; j++) {
                    if (board[i][j] == 'x') {
                        score.back().first += min({i, n - 1 - i, j-1, n - 2 - j});
                        score.back().first -= min({i, n - 1 - i, j, n - 1 - j});
                    } else if (board[i][j] == 'o') {
                        score.back().first += n - min({i, n - 1 - i, j-1, n - 2 - j});
                        score.back().first -= n - min({i, n - 1 - i, j, n - 1 - j});
                    }
                }
            }
            if (board[i][n - 1] != 'o') {
                score.push_back({0, 'R'});
                if (board[i][n - 1] == 'x') score.back().first = -1;
                for (int j = n - 2; j >= 0; j--) {
                    if (board[i][j] == 'x') {
                        score.back().first += min({i, n - 1 - i, j+1, n - j});
                        score.back().first -= min({i, n - 1 - i, j, n - 1 - j});
                    } else if (board[i][j] == 'o') {
                        score.back().first += n - min({i, n - 1 - i, j+1, n - j});
                        score.back().first -= n - min({i, n - 1 - i, j, n - 1 - j});
                    }
                }
            }
            if (board[0][i] != 'o') {
                score.push_back({0, 'U'});
                if (board[0][i] == 'x') score.back().first = -1;
                for (int j = 1; j < n; j++) {
                    if (board[j][i] == 'x') {
                        score.back().first += min({j-1, n - 2 - j, i, n - 1 - i});
                        score.back().first -= min({j, n - 1 - j, i, n - 1 - i});
                    } else if (board[j][i] == 'o') {
                        score.back().first += n - min({j-1, n - 2 - j, i, n - 1 - i});
                        score.back().first -= n - min({j, n - 1 - j, i, n - 1 - i});
                    }
                }
            }
            if (board[n - 1][i] != 'o') {
                score.push_back({0, 'D'});
                if (board[n - 1][i] == 'x') score.back().first = -1;
                for (int j = n - 2; j >= 0; j--) {
                    if (board[j][i] == 'x') {
                        score.back().first += min({j+1, n - j, i, n - 1 - i});
                        score.back().first -= min({j, n - 1 - j, i, n - 1 - i});
                    } else if (board[j][i] == 'o') {
                        score.back().first += n - min({j+1, n - j, i, n - 1 - i});
                        score.back().first -= n - min({j, n - 1 - j, i, n - 1 - i});
                    }
                }
            }
            for (auto s : score) {
                if (s.first < bestScore) {
                    bestScore = s.first;
                    best = {s.second, i};
                }
            }
        }
        cout << best.first << ' ' << best.second << endl;
        if (best.first == 'U') {
            for (int i = 1; i < n; i++)
                board[i - 1][best.second] = board[i][best.second];
            board[n - 1][best.second] = '.';
        } else if (best.first == 'D') {
            for (int i = n - 2; i >= 0; i--)
                board[i + 1][best.second] = board[i][best.second];
            board[0][best.second] = '.';
        } else if (best.first == 'L') {
            for (int i = 1; i < n; i++)
                board[best.second][i - 1] = board[best.second][i];
            board[best.second][n - 1] = '.';
        } else if (best.first == 'R') {
            for (int i = n - 2; i >= 0; i--)
                board[best.second][i + 1] = board[best.second][i];
            board[best.second][0] = '.';
        }
        demon = countDemon(board, n);
    }
}
