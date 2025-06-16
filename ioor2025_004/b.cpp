#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n, x, sum = 0;
    cin >> n >> x;
    vector<int> a(n-1);
    for(auto &x : a){
        cin >> x;
        sum += x;
    }
    sort(a.begin(), a.end());
    for(int i = 0; i <= 100; i++){
        int ans = sum + i;
        ans -= min(i, a[0]);
        ans -= max(i, a[n-2]);
        if(ans >= x){
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;
}
