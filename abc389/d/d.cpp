#include <iostream>
#include <cmath>

using namespace std;

int main() {
    long long r;
    cin >> r;
    long long count = 0;
    double r_squared = r * r;
    for (int i = 1; i < r; i++) {
        double max_j = sqrt(r_squared - (i + 0.5) * (i + 0.5)) - 0.5;
        if (max_j < 1) break; 
        count += (int)max_j; 
    }
    cout << 1 + (r - 1) * 4 + count * 4 << endl;
}
