#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> kmp(const string &p) {
    int m = p.size();
    vector<int> pi(m, 0);
    int j = 0;
    for (int i = 1; i < m; i++) {
        while (j > 0 && p[i] != p[j]) {
            j = pi[j - 1];
        }
        if (p[i] == p[j]) {
            j++;
        }
        pi[i] = j;
    }
    return pi;
}

int main() {
    string s;
    cin >> s;

    string rev = s;
    reverse(rev.begin(), rev.end());
    if (s == rev) {
        cout << s << "\n";
        return 0;
    }

    string t = s + '#' + rev;
    vector<int> pi = kmp(t);
    int check = pi.back();
    string add = rev.substr(0, rev.size() - check);
    cout << s + add << "\n";
}
