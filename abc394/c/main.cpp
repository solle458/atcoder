#include <iostream>

using namespace std;

int main(){
    string s;
    cin >> s;
    int n = s.size();
    for(int i = 0; i < n-1; i++){
        if(s.substr(i, 2) == "WA"){
            s[i] = 'A';
            s[i+1] = 'C';
            int j = i;
            while (j > 0 && s[j-1] == 'W' && s[j] == 'A')
            {
                s[j-1] = 'A';
                s[j] = 'C';
                j--;
            }
        }
    }
    cout << s << endl;
}
