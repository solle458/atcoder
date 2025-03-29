#include <iostream>

using namespace std;

int main(){
    int n;
    string s, t;
    cin >> n >> s >> t;
    int ans = 0;
    for (int i = 0; i < n; i++) if (s[i] != t[i])ans++;
    cout << ans << endl;
}
