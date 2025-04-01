#include <iostream>

using namespace std;

int main(){
    int n;
    cin >> n;
    int ans = 0;
    for(int i = 1; i <= n*7; i++){
        int a;
        cin >> a;
        ans += a;
        if(i % 7 == 0){
            cout << ans << (i == n*7 ? "\n" : " ");
            ans = 0;
        }
    }
}
