#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n;
    long long W;
    cin >> n >> W;
    vector<long long> w(n), v(n);
    for(int i = 0; i < n; i++)cin >> w[i] >> v[i];
    vector<vector<long long>> items(4);
    for(int i = 0; i < n; i++) items[w[i]-w[0]].push_back(v[i]);
    for(int i = 0; i < 4; i++) sort(items[i].rbegin(), items[i].rend());
    vector<vector<long long>> val(4);
    for(int i = 0; i < 4; i++){
        val[i].push_back(0);
        for(auto &x : items[i])val[i].push_back(val[i].back()+x);
    }
    long long ans = 0;
    for(int i = 0; i < int(val[0].size()); i++){
        for(int j = 0; j < int(val[1].size()); j++){
            for(int k = 0; k < int(val[2].size()); k++){
                for(int l = 0; l < int(val[3].size()); l++){
                    long long weight = i*w[0]+j*(w[0]+1)+k*(w[0]+2)+l*(w[0]+3);
                    if(weight <= W)ans = max(ans, val[0][i]+val[1][j]+val[2][k]+val[3][l]);
                }
            }
        }
    }
    cout << ans << endl;
}
