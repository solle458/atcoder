#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> ans(n, vector<int>(n));
    int now = 1;
    for(int i = 0; i < n/2; i++){
        for(int j = 0; j < n-2*i; j++){
            ans[i][i+j] = now;
            now++;
        }
        for(int j = 0; j < n-1-2*i; j++){
            ans[1+i+j][n-1-i] = now;
            now++;
        }
        for(int j = 0; j < n-1-2*i; j++){
            ans[n-1-i][n-2-i-j] = now;
            now++;
        }
        for(int j = 0; j < n-2-2*i; j++){
            ans[n-2-i-j][i] = now;
            now++;
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == n/2 && j == n/2) cout << "T ";
            else cout << ans[i][j] << " ";
        }
        cout << endl;
    }
}
