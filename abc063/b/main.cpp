#include <iostream>
#include <set>

using namespace std;

int main(){
    string s;
    cin >> s;
    set<char> st;
    for(auto &c : s){
        if(st.find(c) != st.end()){
            cout << "no" << endl;
            return 0;
        }
        st.insert(c);
    }
    cout << "yes" << endl;
}
