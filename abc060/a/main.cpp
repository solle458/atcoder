#include <iostream>

using namespace std;

int main(){
    string a, b, c;
    cin >> a >> b >> c;
    cout << (a.back() == b.front() and b.back() == c.front() ? "YES" : "NO") << endl;
}
