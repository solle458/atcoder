#include <iostream>

using namespace std;

int main(){
    string s, ans = "";
    cin >> s;
    for(auto c : s){
        if(c == '0') ans += '0';
        else if(c == '1') ans += '1';
        else if(!ans.empty()) ans.pop_back();
    }
    cout << ans << endl;
}
