#include <iostream>
#include <set>

using namespace std;

int main() {
    int n, r, c;
    cin >> n >> r >> c;
    string s, ans = "";
    cin >> s;
    set<pair<int, int>> st;
    st.insert(make_pair(0, 0));
    int x = 0, y = 0;
    for (int i = 0; i < n; i++) {
        if(s[i] == 'N') x--;
        else if(s[i] == 'S') x++;
        else if(s[i] == 'W') y--;
        else y++;
        if(st.find(make_pair(r-x, c-y)) != st.end()) ans += "1";
        else ans += "0";
        if(st.find(make_pair(-x, -y)) == st.end()) st.insert(make_pair(-x, -y));
    }
    cout << ans << endl;
}
