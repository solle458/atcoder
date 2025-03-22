#include <iostream>
#include <vector>

using namespace std;

int main(){
    int h, w, k;
    cin >> h >> w >> k;
    vector<string> c(h);
    for(auto &s : c) cin >> s;

    for(int i = 0; i < k; i++){
        pair<int, int> max_r = {0, 0}, max_c = {0, 0};
        for(int j = 0; j < h; j++){
            int tmp_r = 0;
            for(int l = 0; l < w; l++){
                if(c[j][l] == '.') tmp_r++;
            }
            if(tmp_r > max_r.first){
                max_r.first = tmp_r;
                max_r.second = j;
            }
        }
        for(int j = 0; j < w; j++){
            int tmp_c = 0;
            for(int l = 0; l < h; l++){
                if(c[l][j] == '.') tmp_c++;
            }
            if(tmp_c > max_c.first){
                max_c.first = tmp_c;
                max_c.second = j;
            }
        }
        if(max_r.first >= max_c.first) {
            for(int j = 0; j < w; j++) c[max_r.second][j] = '#';
        } else {
            for(int j = 0; j < h; j++) c[j][max_c.second] = '#';
        }
    }

    int ans = 0;
    for(int i = 0; i < h; i++)for(int j = 0; j < w; j++)if(c[i][j] == '#') ans++;

    cout << ans << endl;
}
