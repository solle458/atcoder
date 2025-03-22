#include <iostream>

using namespace std;

int main(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++){
        if(n%2 == 1){
            if(n/2+1 == i)cout << "=";
            else cout << "-";
        }else{
            if(n/2 == i)cout << "=";
            else if(n/2+1 == i)cout << "=";
            else cout << "-";
        }
    }
    cout << endl;
}
