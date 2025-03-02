#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <algorithm>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    map<int, deque<int>> mp;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        mp[a[i]].push_back(i);
    }
    long long ans = 1e9;
    for(int i = 0; i < n; i++){
        int d = a[i];
        mp[d].pop_front();
        if(!mp[d].empty()) ans = min(ans, (long long)mp[d].front() - i + 1);
    }
    cout << (ans == 1e9 ? -1 : ans) << endl;
}
