#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int main() {
    int a, N;
    cin >> a >> N;

    int M = 1;
    while (M <= N) {
        M *= 10;
    }

    vector<int> d(M, -1);
    queue<int> Q;
    d[1] = 0;
    Q.push(1);

    while (!Q.empty()) {
        int c = Q.front();
        Q.pop();
        int dc = d[c];
        long long op1 = 1LL * a * c;
        if (op1 < M && d[op1] == -1) {
            d[op1] = dc + 1;
            Q.push(op1);
        }
        if (c >= 10 && c % 10 != 0) {
            string s = to_string(c);
            string rotated = s.back() + s.substr(0, s.size() - 1);
            int op2 = stoi(rotated);
            if (op2 < M && d[op2] == -1) {
                d[op2] = dc + 1;
                Q.push(op2);
            }
        }
    }

    cout << d[N] << endl;
    return 0;
}
