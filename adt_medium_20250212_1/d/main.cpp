#include <iostream>

using namespace std;

int main(){
    int n, k;
    string s;
    cin >> n >> k >> s;
    for(auto c : s){
        if(c == 'o'){
            if(k > 0){
                cout << "o";
                k--;
            }else{
                cout << "x";
            }
        }else cout << "x";
    }
    cout << endl;
}
