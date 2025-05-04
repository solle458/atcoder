#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<string> s(n), t(n);
    for(int i = 0; i < n; i++) cin >> s[i];
    for(int i = 0; i < n; i++) cin >> t[i];
    int ans = 1e9;
    for(int i = 0; i < 4; i++){
        int cnt = i;
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                if(s[j][k] != t[j][k]){
                    cnt++;
                }
            }
        }
        ans = min(ans, cnt);
        vector<string> tmp(n, string(n, ' '));
        for(int j = 0; j < n; j++)
            for(int k = 0; k < n; k++)
                tmp[j][k] = s[n - k - 1][j];
        s = tmp;
    }
    cout << ans << endl;
}
