#include <iostream>
#include <string>

using namespace std;

int main() {
    string s, t, c;
    cin >> s;
    for(int i = 0; i < 150; i++) t += "io";
    int i = 0, j = 0, ans = 0, n = s.size();
    while(i < n){
        if(s[i] != t[j]){
            c += t[j];
            j++;
            ans++;
        }else{
            c += s[i];
            i++;
            j++;
        }
    }
    if(c.back() == 'i'){
        ans++;
        c += 'o';
    }
    cerr << c << endl;
    cout << ans << endl;
}
