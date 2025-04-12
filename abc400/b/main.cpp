#include <iostream>
#include <cmath>

using namespace std;

int main(){
    long long n, m, x = 0;
    cin >> n >> m;
    for(int i = 0; i <= m; i++){
        x += pow(n, i);
        if(x > 1e9){
            cout << "inf" << endl;
            return 0;
        }
    }
    cout << x << endl;
}
