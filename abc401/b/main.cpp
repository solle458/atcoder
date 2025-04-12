#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<string> s(n);
    for(auto &e : s) cin >> e;
    bool login = false;
    int ans = 0;
    for(int i = 0; i < n; i++){
        if (!login and s[i] == "private") ans++;
        if (s[i] == "login") login = true;
        if (s[i] == "logout") login = false;
    }
    cout << ans << endl;
}
