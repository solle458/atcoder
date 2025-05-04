#include <iostream>
#include <random>
#include <set>
using namespace std;

int main() {
    const int N = 10;
    const int M = 100;

    mt19937 rng(42); // 固定シードで再現性確保
    uniform_int_distribution<int> cost_dist(0, 1000000000);
    uniform_int_distribution<int> zoo_dist(1, N);
    uniform_int_distribution<int> zoo_count_dist(1, 3);

    cout << N << " " << M << endl;
    for (int i = 0; i < N; i++) {
        cout << cost_dist(rng) << " ";
    }
    cout << endl;

    for (int i = 0; i < M; i++) {
        int k = zoo_count_dist(rng);
        set<int> used;
        while ((int)used.size() < k) {
            used.insert(zoo_dist(rng));
        }
        cout << used.size();
        for (int z : used) {
            cout << " " << z;
        }
        cout << endl;
    }
}
