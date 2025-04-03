#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;

    int ans = 0;
    while (!s.empty()) {
        const auto back{s.back()};
        s.pop_back();
        if (back == '0' && s.back() == '0')s.pop_back();
        ++ans;
    }
    cout << ans << endl;
}
