#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

using namespace std;
using namespace chrono;

class SA {
   public:
    vector<vector<int>> mat;
    vector<char> c;
    int l;

    SA(int m, int length, mt19937& rng) {
        mat.resize(m, vector<int>(m, 0));
        c.resize(m);
        for (int i = 0; i < c.size(); i++) {
            c[i] = static_cast<char>((i % 6) + 'a');
        }
        l = length;
    }

    void matChange(mt19937& rng) {
        int change = 1;
        int prev = rng() % mat.size();
        int next = rng() % mat.size();
        int x = rng() % mat.size();
        change = max(0, min(change, mat[x][next]));
        mat[x][prev] += change;
        mat[x][next] -= change;
        int sum = 0;
        for (int j = 0; j < mat[x].size(); j++) {
            sum += mat[x][j];
        }
        if (sum != 100) {
            for (int j = 0; j < 100 - sum; j++) {
                int y = rng() % mat[x].size();
                mat[x][y]++;
            }
        }
    }

    // 部分文字列が生成される基本確率を計算
    double calculateSubstringProbability(const string& substring) {
        if (substring.empty()) return 1.0;

        int len = substring.length();
        vector<int> charIndices;

        // 文字を配列インデックスに変換
        for (char ch : substring) {
            auto it = find(c.begin(), c.end(), ch);
            if (it == c.end()) return 0.0;  // 存在しない文字
            charIndices.push_back(distance(c.begin(), it));
        }

        // 最初の文字の確率（均等分布と仮定）
        double prob = 1.0 / c.size();

        // 連続する文字間の遷移確率を掛け合わせ（/100は0~100を0~1に正規化）
        for (int j = 1; j < len; j++) {
            prob *= mat[charIndices[j - 1]][charIndices[j]] / 100.0;
        }

        return prob;
    }

    // 長さlの文字列内で部分文字列が1回以上出現する確率を計算
    double calculateOccurrenceProbability(const string& substring) {
        int substringLen = substring.length();
        if (substringLen > l) return 0.0;

        // 部分文字列が任意の位置で出現する基本確率
        double probSingle = calculateSubstringProbability(substring);

        // 可能な開始位置の数
        int possiblePositions = l - substringLen + 1;

        // 1回以上出現する確率 = 1 - (1回も出現しない確率)
        // 各位置で独立に出現すると仮定した近似計算
        double probNone = pow(1.0 - probSingle, possiblePositions);
        return 1.0 - probNone;
    }

    long long evaluate(int n, const vector<int>& p, const vector<string>& s) {
        // 各部分文字列の出現確率Qiを計算し、Pi * Qiの総和を求める
        double totalScore = 0.0;

        for (int i = 0; i < n; i++) {
            // 部分文字列s[i]が長さlの文字列に1回以上含まれる確率Qiを計算
            double qi = calculateOccurrenceProbability(s[i]);
            totalScore += p[i] * qi;
        }

        return static_cast<long long>(round(totalScore));
    }
};

void printSA(const SA& sa) {
    for (int i = 0; i < sa.mat.size(); ++i) {
        cout << sa.c[i];
        for (int j = 0; j < sa.mat[i].size(); ++j) {
            cout << " " << sa.mat[i][j];
        }
        cout << endl;
    }
}

void initWeights(SA& sa, int& p1, int& p2, string& s1, string& s2) {
    for (int j = 0; j < s1.size() - 1; j++) {
        char next[2] = {s1[j + 1], s2[j + 1]}, prev[2] = {s1[j], s2[j]};
        for (int k = 0; k < sa.c.size(); k++) {
            if (sa.c[k] == prev[0]) {
                for (int l = 0; l < sa.c.size(); l++) {
                    if (sa.c[l] == next[0]) {
                        sa.mat[k][l] += p1;
                    }
                }
            }
            if (sa.c[k] == prev[1]) {
                for (int l = 0; l < sa.c.size(); l++) {
                    if (sa.c[l] == next[1]) {
                        sa.mat[k][l] += p2;
                    }
                }
            }
        }
    }
    int m = sa.mat.size();
    for (int i = 0; i < m; i++) {
        int total = 0;
        int sum = accumulate(sa.mat[i].begin(), sa.mat[i].end(), 0);
        vector<double> scaled(m, 0.0);
        vector<int> result(m);
        if(sum != 0)for (int j = 0; j < m; j++)scaled[j] = static_cast<double>(sa.mat[i][j]) / sum * 100;
        for (int j = 0; j < m; ++j) {
            result[j] = round(scaled[j]);
            total += result[j];
        }
        while (total != 100) {
            for (int j = 0; j < m && total != 100; ++j) {
                if (total > 100 && result[j] > 0) {
                    result[j]--;
                    total--;
                } else if (total < 100) {
                    result[j]++;
                    total++;
                }
            }
        }
        cout << sa.c[i] << " ";
        for (int j = 0; j < m; j++) {
            sa.mat[i][j] = result[j];
            cout << sa.mat[i][j] << (j == m - 1 ? "\n" : " ");
        }
    }
}

void simulatedAnnealing(int n, int m, int l, vector<int>& p,
                        vector<string>& s) {
    auto start = system_clock::now();

    mt19937 rng(steady_clock::now().time_since_epoch().count());
    SA curSA(m, l, rng), bestSA(m, l, rng);
    initWeights(curSA, p[0], p[1], s[0], s[1]);
    long long curScore = curSA.evaluate(n, p, s);
    long long bestScore = curScore;
    bestSA = curSA;

    double startTemp = 10.0;
    double endTemp = 1e-6;
    double timeLimit = 1.95;
    int printInterval = 100;
    int iteration = 1;

    while (iteration++) {
        auto now = system_clock::now();
        double elapsed =
            duration_cast<milliseconds>(now - start).count() / 1000.0;
        if (elapsed > timeLimit) break;
        double t = elapsed / timeLimit;
        double temperature = startTemp * pow(endTemp / startTemp, t);
        SA newSA = curSA;
        for (int i = 0; i < static_cast<int>(temperature) + 1; i++)
            newSA.matChange(rng);
        long long newScore = newSA.evaluate(n, p, s);
        long long diff = newScore - curScore;

        if (diff >= 0 || exp(diff / temperature) >
                             uniform_real_distribution<>(0.0, 1.0)(rng)) {
            curSA = newSA;
            curScore = newScore;
            if (newScore > bestScore) {
                bestSA = newSA;
                bestScore = newScore;
            }
        }

        if (iteration % printInterval == 0) {
            printSA(bestSA);
            iteration = 1;
        }
    }
    printSA(bestSA);
}

int main() {
    int n, m, l;
    cin >> n >> m >> l;
    vector<pair<int, string>> a(n);
    vector<int> p(n);
    vector<string> s(n);
    for (int i = 0; i < n; i++) cin >> a[i].second >> a[i].first;
    sort(a.begin(), a.end(), greater<pair<int, string>>());
    for (int i = 0; i < n; i++) {
        p[i] = a[i].first;
        s[i] = a[i].second;
    }

    simulatedAnnealing(n, m, l, p, s);
}
