#include <iostream>

using namespace std;

int main(){
    string s = "rsp";
    for(auto c : s){
        for(auto d : s){
            cout << c << d << endl;
        }
    }
}
