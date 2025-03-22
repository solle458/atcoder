#include <iostream>
#include <map>

using namespace std;

int main(){
    map<int, int> m;
    for(int i = 0; i < 7; i++){
        int a;
        cin >> a;
        m[a]++;
    }
    bool two = false, three = false;
    for(auto p : m){
        if(!three and p.second >= 3)three = true;
        else if(p.second >= 2)two = true;
    }
    cout << (two && three ? "Yes" : "No") << endl;
}
