#include <iostream>

using namespace std;

int main(){
    int r, x;
    cin >> r >> x;
    if(x == 1){
        cout << (1600 <= r and r <= 2999 ? "Yes" : "No") << endl;
    }else{
        cout << (1200 <= r and r <= 2399 ? "Yes" : "No") << endl;
    }
}
