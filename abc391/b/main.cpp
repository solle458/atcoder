#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<string> s(n), t(m);
    for (int i = 0; i < n; i++) cin >> s[i];
    for (int i = 0; i < m; i++) cin >> t[i];
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            bool ok = true;
            for(int k = 0; k < m; k++){
                if(i+k >= n){
                    ok = false;
                    break;
                }
                for(int l = 0; l < m; l++){
                    if(j+l >= n){
                        ok = false;
                        break;
                    }
                    if(s[i+k][j+l] != t[k][l]){
                        ok = false;
                        break;
                    }
                }
                if(!ok) break;
            }
            if(ok){
                cout << i+1 << " " << j+1 << endl;
                return 0;
            }
        }
    }
}
