#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x : a)cin >> x;
    int q;
    cin >> q;
    while(q--){
        int v, k, x;
        cin >> v;
        if(v == 1){
            cin >> k >> x;
            a[k-1] = x;
        }else{
            cin >> k;
            cout << a[k-1] << endl;
        }
    }
}
