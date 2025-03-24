#include <iostream>

using namespace std;

int main() {
    string s;
    cin >> s;
    int l = -1, r = -1;
    for (int i = 0; i+1 < s.size(); ++i) {
        if (s[i] == s[i+1]) l = i+1, r = i+2;
        if (i+2 < s.size() && s[i] == s[i+2]) l = i+1, r = i+3;
    }
    cout << l << " " << r << endl;
}
