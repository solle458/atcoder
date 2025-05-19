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

int main(){
    mt19937 rng; // Create a persistent mt19937 object
    SA sa(12, 10, rng), bestSA(12, 10, rng);
    sa.matChange(rng);
    bestSA = sa;
    sa.matChange(rng);
    for(auto & row : sa.mat) {
        for(auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
    cout << "Best SA:" << endl;
    for(auto & row : bestSA.mat) {
        for(auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}
