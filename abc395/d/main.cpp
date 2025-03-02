#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main(){
    int n, q;
    cin >> n >> q;
    vector<int> bird(n);
    vector<set<int>> home(n);
    for(int i = 0; i < n; i++){
        bird[i] = i;
        home[i].insert(i);
    }
    for(int Q = 0; Q < q; Q++){
        int x, a, b;
        cin >> x;
        if(x == 1){
            cin >> a >> b;
            a--; b--;
            home[bird[a]].erase(a);
            home[b].insert(a);
            bird[a] = b;
        }else if(x == 2){
            cin >> a >> b;
            a--; b--;
            home[a].swap(home[b]);
            for(auto i : home[a]){
                bird[i] = a;
            }
            for(auto i : home[b]){
                bird[i] = b;
            }
        }else{
            cin >> a;
            a--;
            cout << bird[a]+1 << endl;
        }
    }
}
