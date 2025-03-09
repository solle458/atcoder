#include <iostream>
#include <string>
using namespace std;

int main(){
    int l, r;
    string s;
    cin >> l >> r >> s;
    string rev = s.substr(l-1, r-l+1);
    reverse(rev.begin(), rev.end());
    s = s.substr(0, l-1) + rev + s.substr(r);
    cout << s << endl;
}
