#include <iostream>
#include <vector>

using namespace std;

int main(){
    string s, t;
    cin >> s;
    vector<bool> a(26, false);
    for(int i = 0; i < s.size(); i++){
        char c = s[i];
        t.push_back(c);
        if('a' <= c and c <= 'z' and a[c-'a']){
            cout << "No" << endl;
            return 0;
        }
        if(c == ')'){
            while(t.back() != '('){
                if('a' <= t.back() and t.back() <= 'z')a[t.back()-'a'] = false;
                t.pop_back();
            }
            t.pop_back();
        }else if(c != '('){
            a[c-'a'] = true;
        }
    }
    cout << "Yes" << endl;
}
