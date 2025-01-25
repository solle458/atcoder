#include <iostream>
#include <vector>

using namespace std;

int main(){
    int h, w, maxX = -1, minX = 1e9, maxY = -1, minY = 1e9;
    cin >> h >> w;
    vector<string> s(h);
    for(auto &x : s)cin >> x;
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            if(s[i][j] == '#'){
                maxX = max(maxX, j);
                minX = min(minX, j);
                maxY = max(maxY, i);
                minY = min(minY, i);
            }
        }
    }
    for(int i = minY; i <= maxY; i++){
        for(int j = minX; j <= maxX; j++){
            if(s[i][j] == '.'){
                cout << "No" << endl;
                return 0;
            }
        }
    }
    cout << "Yes" << endl;
}
