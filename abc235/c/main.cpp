#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main(){
    int n, q;
    cin >> n >> q;
    map<int, vector<int>> mp;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        mp[a].push_back(i);
    }
    while(q--){
        int x, k;
        cin >> x >> k;
        if(mp[x].size() < k){
            cout << -1 << endl;
        } else {
            cout << mp[x][k-1] + 1 << endl;
        }
    }
}
