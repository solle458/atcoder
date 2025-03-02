#include <iostream>
#include <map>

using namespace std;

int main() {
    string s, st = "";
    cin >> s;
    map<char, char> mp = {{')', '('}, {']', '['}, {'>', '<'}};
    for (auto c : s) {
        if (st == "" or st.back() != mp[c]) st.push_back(c);
        else st.pop_back();
    }
    cout << (st == "" ? "Yes" : "No") << endl;
}
