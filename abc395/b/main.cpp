#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int d = min(min(i, j), min(n-1-i, n-1-j));
            cout << (d%2 == 0 ? '#':'.') << (j == n-1 ? "\n" : "");
        }
    }
}
