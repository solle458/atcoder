#include <iostream>
#include <cmath>

using namespace std;

int main() {
	long long n;
	cin >> n;

	long long y = 1, x = cbrt(n + 1);
	while (3 * y * y + 3 * y + 1 <= n) {
		while (x * x * x - y * y * y < n) x++;
		if (x * x * x - y * y * y == n) {
			cout << x << ' ' << y << endl;
			return 0;
		}
		x--;
		y++;
	}

	cout << -1 << endl;
}
