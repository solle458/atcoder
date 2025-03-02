#include <iostream>
#include <set>

using namespace std;

int main(){
    int n, m, ans = 0;
    cin >> n >> m;
    set<pair<int, int>> s;
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--; b--;
        if(a == b) ans++;
        else if(s.count(make_pair(a, b)) || s.count(make_pair(b, a))) ans++;
        s.insert(make_pair(a, b));
        s.insert(make_pair(b, a));
    }
    cout << ans << endl;
}
