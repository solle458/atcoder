#include <iostream>

using namespace std;

int main(){
    int a[3];
    cin >> a[0] >> a[1] >> a[2];
    if(a[0]*a[1] == a[2] or a[1]*a[2] == a[0] or a[2]*a[0] == a[1])cout << "Yes" << endl;
    else cout << "No" << endl;
}
