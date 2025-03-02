#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<string> s(n);
    vector<pair<int,int>> id(n);
    for(int i = 0; i < n; i++){
        cin >> s[i];
        id[i].first = s[i].size();
        id[i].second = i;
    }
    sort(id.begin(), id.end());
    for(int i = 0; i < n; i++) cout << s[id[i].second] << (i == n-1 ? "\n" : "");
}
