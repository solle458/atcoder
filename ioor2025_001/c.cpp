#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
    }
    string s;
    cin >> s;
    vector<pair<int, int>> rs;
    map<int, vector<int>> ls;
    for(int i = 0; i < n; i++){
        if(s[i] == 'R'){
            rs.push_back(a[i]);
        }else{
            ls[a[i].second].push_back(a[i].first);
        }
    }
    for(auto it = ls.begin(); it != ls.end(); it++){
        sort(it->second.begin(), it->second.end());
    }
    for(int i = 0; i < rs.size(); i++){
        int x = rs[i].first;
        int y = rs[i].second;
        if(ls.count(y) != 0){
            auto it = lower_bound(ls[y].begin(), ls[y].end(), x);
            if(it != ls[y].end()){
                cout << "Yes" << endl;
                return 0;
            }
        }
    }
    cout << "No" << endl;
}
