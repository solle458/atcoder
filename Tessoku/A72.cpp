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
        int tmp_c = 0;
        for(int j = 0; j < h; j++){
            int tmp_r = 0;
            for(int k = 0; k < w; k++){
                if(c[j][k] == '.')tmp_r++;
            }
            if(tmp_r > max_r.first){
                max_r.first = tmp_r;
                max_r.second = j;
            }
        }
    }
}
