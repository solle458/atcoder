#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    map<int, int> m;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        m[a[i]]++;
    }
    int ans = -1;
    for(auto i = m.rbegin(); i != m.rend(); i++){
        if(i -> second == 1){
            ans = i->first;
            break;
        }
    }
    if(ans != -1){
        for(int i = 0; i < n; i++){
            if(a[i] == ans){
                cout << i + 1 << endl;
                return 0;
            }
        }
    }
    cout << -1 << endl;
}
