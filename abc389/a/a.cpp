#include <iostream>

using namespace std;

int main(){
    string s;
    cin >> s;
    cout << (int)(s[0] - '0') * (int)(s[2] - '0') << endl;
}
