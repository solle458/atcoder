#include <iostream>

using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        string s;
        cin >> n >> s;
        int start = -1;
        for(int i = 0; i < n-1; i++){
            if(s[i] > s[i+1]){
                start = i+1;
                break;
            }
        }
        if(start == -1){
            cout << s << endl;
            continue;
        }
        int end = -1;
        for(int i = start+1; i < n; i++){
            if(s[i] > s[start-1]){
                end = i-1;
                break;
            }
        }
        string ans = "";
        if(end == -1){
            for(int i = 0; i < start-1; i++)ans += s[i];
            ans += s[start];
            for(int i = start+1; i < n; i++)ans += s[i];
            ans += s[start-1];
        }else{
            for(int i = 0; i < start-1; i++)ans += s[i];
            ans += s[start];
            for(int i = start+1; i <= end; i++)ans += s[i];
            ans += s[start-1];
            for(int i = end+1; i < n; i++)ans += s[i];
        }
        cout << ans << endl;
    }
}
