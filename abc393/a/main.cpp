#include <iostream>

using namespace std;

int main(){
    string s1, s2;
    cin >> s1 >> s2;
    if(s1 == s2){
        if(s1 == "fine") cout << 4 << endl;
        else cout << 1 << endl;
    }else if(s1 == "fine") cout << 3 << endl;
    else cout << 2 << endl;
}
