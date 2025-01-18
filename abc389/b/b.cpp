#include <iostream>

using namespace std;

int main(){
    long long x, n = 1, m = 1;
    cin >> x;
    while (m != x){
        m *= n;
        n++;
    }
    cout << n-1 << endl;
}
