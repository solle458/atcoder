#include <iostream>

using namespace std;

int main(){
    int n, ans = -1;
    cin >> n;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        if(ans < a)ans = a;
        else break;
    }
    cout << ans << endl;
}
