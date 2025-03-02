#include <iostream>
#include <map>

using namespace std;

int main(){
    int n;
    cin >> n;
    map<string, int> mp;
    for(int i = 0; i < n ; i++){
        string s;
        cin >> s;
        mp[s]++;
    }
    int max = 0;
    string ans;
    for(auto it = mp.begin(); it != mp.end(); it++){
        if(it->second > max){
            max = it->second;
            ans = it->first;
        }
    }
    cout << ans << endl;
}
