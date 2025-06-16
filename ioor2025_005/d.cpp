#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

int main(){
    string s;
    map<char, string> m;
    for(int i = 0; i < 3; i++){
        cin >> s;
        reverse(s.begin(), s.end());
        m['a' + i] = s;
    }
    char now = 'a', prev = 'a';
    while(m[now].size() > 0){
        prev = now;
        now = m[now].back();
        m[prev].pop_back();
    }
    char ans = 'A'+(now - 'a');
    cout << ans << endl;
}
