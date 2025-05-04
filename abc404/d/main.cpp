#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<long long> c;
vector<vector<int>> zoo;
long long ans = 1e18;

void search(){
    const int MAX_VISIT = 3;
    int size = 1;
    for (int i = 0; i < n; i++) size *= MAX_VISIT;

    for (int mask = 0; mask < size; mask++){
        vector<int> visits(n, 0);
        int tmp = mask;
        for (int i = 0; i < n; i++) {
            visits[i] = tmp % MAX_VISIT;
            tmp /= MAX_VISIT;
        }

        vector<int> anim(m, 0);
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            sum += visits[i] * c[i];
            for (int v = 0; v < visits[i]; v++) {
                for (int a : zoo[i]) {
                    anim[a]++;
                }
            }
        }

        bool ok = true;
        for (int x : anim) {
            if (x < 2) ok = false;
        }
        if (ok) ans = min(ans, sum);
    }
}

int main(){
    cin >> n >> m;
    c.resize(n);
    for (int i = 0; i < n; i++) cin >> c[i];

    zoo.resize(n);
    for (int i = 0; i < m; i++) {
        int K;
        cin >> K;
        for (int j = 0; j < K; j++) {
            int z;
            cin >> z;
            zoo[z-1].push_back(i);
        }
    }

    search();
    cout << ans << endl;
}
