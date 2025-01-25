#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n, q;
    cin >> n >> q;
    vector<int> a(q);
    vector<bool> b(n, true);
    for(auto &x: a){
        cin >> x;
        if(b[x-1]) b[x-1] = false;
        else b[x-1] = true;
    }
    int ans = 0;
    for(auto f : b)if(f)ans++;
    cout << ans << endl;
}
