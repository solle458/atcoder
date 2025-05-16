#include <iostream>

using namespace std;

int main(){
    string s;
    cin >> s;
    int ans = 0;
    for(auto c : s){
        int now = c - '0';
        ans += now + 10*now + 100*now;
    }
    cout << ans << endl;
}
