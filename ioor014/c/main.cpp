#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main(){
    int n;
    string s;
    cin >> n >> s;
    deque<int> sr;
    for(int i = n-1; i >= 0; i--)if(s[i] == 'R')sr.push_back(i);
    int ans = 0;
    for(int i = 0; i < n; i++){
        if(s[i] == 'W'){
            if(sr.empty()) continue;
            int j = sr.front();
            sr.pop_front();
            ans++;
            swap(s[i], s[j]);
        }else{
            sr.pop_back();
        }
    }
    cerr << s << endl;
    cout << ans << endl;
}
