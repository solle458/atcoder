#include <iostream>
#include <vector>
#include <atcoder/dsu>

using namespace std;
using namespace atcoder;

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> edge(n);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u--;v--;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    int connected = 0;
    vector<bool> already(n);
    int erase = 0;
    dsu uf(n);
    for(int i = 0; i < n; i++){
        connected++;
        if(already[i]){
            erase--;
        }
        for(const auto j : edge[i]){
            if(j < i){
                if(!uf.same(i, j)){
                    uf.merge(i, j);
                    connected--;
                }
            }else{
                if(!already[j])erase++;
                already[j] = true;
            }
        }
        if(connected == 1){
            cout << erase << endl;
        }else{
            cout << -1 << endl;
        }
    }
}
