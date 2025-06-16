#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n), ans;
    vector<bool> f(n, false);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < n; i++){
        if(!f[i]){
            f[a[i]-1] = true;
        }
    }
    for(int i = 0; i < n; i++){
        if(!f[i]){
            ans.push_back(i);
        }
    }
    cout << ans.size() << endl;
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i]+1 << " ";
    }
    cout << endl;
}
