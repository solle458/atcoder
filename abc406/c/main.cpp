#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> p(n), u, l;
    for(auto &i : p) cin >> i;
    long long ans = 0, prev = 0;
    for(int i = 1; i < n-1; i++){
        if(p[i-1] < p[i] and p[i] > p[i+1]){
            u.push_back(i);
        }
        if(p[i-1] > p[i] and p[i] < p[i+1]){
            if(u.size() == 0)prev = i;
            l.push_back(i);
        }
    }
    for(int i = 0; i < u.size(); i++){
        auto lower = lower_bound(l.begin(), l.end(), u[i]);
        if (lower == l.end()) continue;
        if(i != u.size()-1){
            ans += (u[i+1] - *lower) * (u[i] - prev);
            prev = *lower;
        } else {
            ans += (n - 1 - *lower) * (u[i] - prev);
        }
    }
    
    cout << ans << endl;
}
