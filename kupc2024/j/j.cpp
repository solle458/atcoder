#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string s, k = "KUPC";
    long long l;
    cin >> s >> l;
    map<char, long long> m;
    for(int i = 0; i < s.size(); i++) {
        m[s[i]]++;
    }
    long long ans = 0;
    for(char c : k) {
        if(m[c] == 0) {
            cout << -1 << endl;
            return 0;
        }
        long long tmp = 0;
        for(char d : k) {
            if(c == d){
                tmp += l / m[d];
                if(l % m[c] != 0)tmp++;
            }else{
                long long cnt = 0;
                tmp = 1;
                for(char str : s){
                    if(str == c)break;
                    if(str == d)cnt++;
                }
                tmp += (l-1-cnt)/m[d];
                if((l-1-cnt) % m[d] != 0)tmp++;
            }
            ans = max(ans, tmp);
        }
    }
    cout << ans << endl;
}
