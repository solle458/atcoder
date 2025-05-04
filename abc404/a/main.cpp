#include <iostream>
#include <vector>

using namespace std;

int main(){
    string s;
    cin >> s;
    vector<bool> a(26, false);
    for(int i = 0; i < s.size(); i++){
        a[s[i] - 'a'] = true;
    }
    for(int i = 0; i < 26; i++){
        if(!a[i]){
            cout << (char)(i + 'a') << endl;
            return 0;
        }
    }
}
