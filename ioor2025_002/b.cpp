#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n), pos(n);
    vector<pair<int, int>> ans;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i] - 1] = i;
    }
    for(int i = 0; i < n; i++){
        if(a[i] != i + 1){
            int j = pos[i];
            swap(a[i], a[j]);
            swap(pos[i], pos[a[j]-1]);
            ans.push_back({i+1, j+1});
        }
    }
    cout << ans.size() << endl;
    for(auto& p : ans) cout << p.first << " " << p.second << endl;
}
