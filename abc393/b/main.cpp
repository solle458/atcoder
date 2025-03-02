#include <iostream>

using namespace std;

int main(){
    string s;
    cin >> s;
    int ans = 0, n = s.size();
    for(int i = 0; i < n; i++){
        if(s[i] == 'A'){
            for(int j = i+1; j < n; j++){
                if(s[j] == 'B'){
                    int dist = j - i;
                    if(dist+j < n && s[dist+j] == 'C'){
                        ans++;
                    }
                }
            }
        }
    }
    cout << ans << endl;
}
