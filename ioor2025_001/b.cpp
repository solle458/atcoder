#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n), b;
    set<int> s;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        s.insert(a[i]);
    }
    for(auto it : s){
        b.push_back(it);
    }
    sort(b.begin(), b.end());
    vector<int> ans(n);
    for(int i = 0; i < n; i++){
        auto it = b.size() - (upper_bound(b.begin(), b.end(), a[i]) - b.begin());
        ans[it]++;
    }
    for(int i = 0; i < n; i++){
        cout << ans[i] << endl;
    }
}
