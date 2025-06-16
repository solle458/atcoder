#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    int a = 0, t = 0;
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        t += x;
        a += y;
    }
    if(a == t){
        cout << "Draw" << endl;
        return 0;
    }
    cout << (t > a ? "Takahashi" : "Aoki") << endl;
}
