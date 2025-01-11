#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    int n, ans = 0;
    cin >> n;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        ans += max(0, a - 10);
    }
    cout << ans << endl;
}
