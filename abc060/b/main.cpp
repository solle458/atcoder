#include <iostream>

using namespace std;

int main(){
    long long a, b, c;
    cin >> a >> b >> c;
    long long mod = a%b, s = a%b;
    for(int i = 0; i < b+1; i++){
        if(s == c){
            cout << "YES" << endl;
            return 0;
        }
        s = (s+mod)%b;
    }
    cout << "NO" << endl;
}
