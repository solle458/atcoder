#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    int n;
    string s;
    cin >> n >> s;
    int l = 0, r = n-1, center = n/2;
    for (int i = 0; i <= n / 2; i++) {
        if (n / 2 - i >= 0 && s[n / 2 - i] == '1') {
            center = n / 2 - i;
            l = center-1;
            r = center+1;
            break;
        }
        if (n / 2 + i < n && s[n / 2 + i] == '1') {
            center = n / 2 + i;
            l = center-1;
            r = center+1;
            break;
        }
    }
    int ans = 0, cp = center;
    center--;
    while(center >= 0){
        if(s[center] == '1'){
            ans += l-center;
            l--;
        }
        center--;
    }
    center = cp+1;
    while(center < n){
        if(s[center] == '1'){
            ans += center-r;
            r++;
        }
        center++;
    }
    cout << ans << endl;
}
