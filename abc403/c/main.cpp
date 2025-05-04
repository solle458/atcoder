#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main(){
    int n, m, q;
    cin >> n >> m >> q;
    vector<set<int>> u(n+1);
    for(int i = 0; i < q; i++){
        int v, x, y;
        cin >> v;
        if(v == 1){
            cin >> x >> y;
            u[x].insert(y);
        } else if(v == 2){
            cin >> x;
            u[x].insert(m+1);
        } else {
            cin >> x >> y;
            cout << ((u[x].count(y) or u[x].count(m+1)) ? "Yes" : "No") << endl;
        }
    }
}
