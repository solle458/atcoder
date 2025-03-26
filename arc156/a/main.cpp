#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        int n;
        string s;
        cin >> n >> s;
        int one = count(s.begin(), s.end(), '1');
        if (one & 1){
            cout << -1 << endl;
            continue;
        }
        bool adj = false;
        for (int i = 0; i < n - 1; i++)if(s.substr(i, 2) == "11") adj = true;
        if (one != 2 or !adj){
            cout << one/2 << endl;
            continue;
        }
        if (n == 3){
            cout << -1 << endl;
            continue;
        }
        if (n == 4 and s == "0110"){
            cout << 3 << endl;
            continue;
        }
        cout << 2 << endl;
    }
}
