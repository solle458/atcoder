#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    map<int, int> pos;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        a[i]--;
        pos[a[i]] = i;
    }
    vector<pair<int, int>> ans;
    for(int i = 0; i < n; i++){
        if(a[i] != i){
            int j = pos[i];
            pos[a[i]] = j;
            pos[i] = i;
            swap(a[i], a[j]);
            ans.push_back({i, j});
        }
    }
    cout << ans.size() << endl;
    for(auto [f, s] : ans) cout << f+1 << " " << s+1 << endl;
}
