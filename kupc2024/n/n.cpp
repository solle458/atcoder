#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    if(n == 2){
        cout << "No" << endl;
        return 0;
    }
    if(n%2 == 1){
        cout << "Yes" << endl;
        vector<int> a(n);
        for(int i = 0; i < n; i++) a[i] = -n/2+i;
        vector<vector<int>> ans(n, vector<int>(n));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                ans[i][(i+j)%n] = a[j];
            }
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cout << ans[i][j] << " ";
            }
            cout << endl;
        }
    }else{
        cout << "Yes" << endl;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            if(i >= n/2) a[i] = -n/2+i+1;
            else a[i] = -n/2+i;
        }
        vector<vector<int>> ans(n, vector<int>(n));
        for(int i = 0; i < n/2; i++){
            for(int j = 0; j < n; j++){
                ans[i][(i+j)%n] = a[j]+i;
            }
        }
        int cnt = n/2 - 1;
        for(int i = n/2; i < n; i++){
            for(int j = 0; j < n; j++){
                ans[i][(i+j)%n] = a[j] - cnt;
            }
            cnt--;
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cout << ans[i][j] << " ";
            }
            cout << endl;
        }
    }
}
