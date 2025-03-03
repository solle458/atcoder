#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for(auto &x : a)cin >> x;
    for(auto &x : b)cin >> x;
    map<int, int> mp;
    for(int i = 0; i < n; i++){
        if(mp.empty()){
            mp[a[i]] = i;
            continue;
        }
        if(mp.begin()->first > a[i])mp[a[i]] = i;
    }
    for(auto &x : b){
        auto ub = mp.upper_bound(x);
        if(ub == mp.begin()){
            cout << -1 << endl;
            continue;
        }
        cout << prev(ub)->second + 1 << endl;
    }
}
