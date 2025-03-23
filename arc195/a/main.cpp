#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for(auto &x : a) cin >> x;
    for(auto &x : b) cin >> x;
    deque<int> l, r;
    int now_l = 0, now_r = 0;
    for(int i = 0; i < n; i++){
        if(now_l < m and a[i] == b[now_l]){
            l.push_back(i);
            now_l++;
        }
        if(m-now_r-1 >= 0 and a[n-i-1] == b[m-now_r-1]){
            r.push_front(n-i-1);
            now_r++;
        }
    }
    if(l.size() == m and r.size() == m and l != r) cout << "Yes" << endl;
    else cout << "No" << endl;
}
