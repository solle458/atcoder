#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main(){
    vector<int> h(3), w(3);
    vector<set<pair<int, int>>> seat(2);
    cin >> h[0] >> w[0];
    vector<vector<string>> a(3);
    a[0].resize(h[0]);
    for(int i = 0; i < h[0]; i++){
        cin >> a[0][i];
        for(int j = 0; j < w[0]; j++) if(a[0][i][j] == '#')seat[0].insert({i, j});
    }
    cin >> h[1] >> w[1];
    a[1].resize(h[1]);
    for(int i = 0; i < h[1]; i++){
        cin >> a[1][i];
        for(int j = 0; j < w[1]; j++) if(a[1][i][j] == '#')seat[1].insert({i, j});
    }
    set<pair<int, int>> x;
    cin >> h[2] >> w[2];
    a[2].resize(h[2]);
    for(int i = 0; i < h[2]; i++){
        cin >> a[2][i];
        for(int j = 0; j < w[2]; j++) if(a[2][i][j] == '#')x.insert({i, j});
    }
    for(int i = -h[0]-1; i <= h[0]+1; i++){
        for(int j = -w[0]-1; j <= w[0]+1; j++){
            for(int k = -h[1]-1; k <= h[1]+1; k++){
                for(int l = -w[1]-1; l <= w[1]+1; l++){
                    set<pair<int, int>> ans;
                    bool all = true;
                    for(auto it = seat[0].begin(); it != seat[0].end(); it++){
                        if(it->first+i >= 0 and it->first+i < h[2] and it->second+j >= 0 and it->second+j < w[2]){
                            ans.insert({it->first+i, it->second+j});
                        }else{
                            all = false;
                        }
                    }
                    for(auto it = seat[1].begin(); it != seat[1].end(); it++){
                        if(it->first+k >= 0 and it->first+k < h[2] and it->second+l >= 0 and it->second+l < w[2]){
                            ans.insert({it->first+k, it->second+l});
                        }else{
                            all = false;
                        }
                        }
                    if(ans == x and all){
                        cout << "Yes" << endl;
                        return 0;
                    }
                }
            }
        }
    }
    cout << "No" << endl;
}
