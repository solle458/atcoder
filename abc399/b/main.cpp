#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n), ans(n);
    map<int, int> m;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        m[a[i]]++;
    }
    int r = 1;
    for(auto it = m.rbegin(); it != m.rend(); it++){
        for(int i = 0; i < n; i++){
            if(a[i] == it->first){
                ans[i] = r;
            }
        }
        r += it->second;
    }
    for(int i = 0; i < n; i++){
        cout << ans[i] << endl;
    }
}
