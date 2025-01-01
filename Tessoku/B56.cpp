#include <iostream>
#include <string>

using namespace std;

int main() {
    int n, q; 
    cin >> n >> q;
    string s; 
    cin >> s;
    string t = "";
    for(int i = 0; i < n; i++) t += s[n-i-1];
    for(int i = 0; i < q; i++) {
        int l, r; 
        cin >> l >> r;
        l--;r--;
        if (s.substr(l,r-l) == t.substr(n-r-1,r-l)) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
}

