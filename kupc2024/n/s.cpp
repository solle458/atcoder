#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    for(int q = 0; q <= n; q++){
    if(n == 2){
        cout << "No" << endl;
        return 0;
    }
    if(q%2 == 1){
        vector<int> a(q);
        for(int i = 0; i < q; i++) a[i] = -q/2+i;
        vector<vector<int>> ans(q, vector<int>(q));
        for(int i = 0; i < q; i++){
            for(int j = 0; j < q; j++){
                ans[i][(i+j)%q] = a[j];
            }
        }
        for(int i = 0; i < q; i++){
            for(int j = 0; j < q; j++){
                cout << ans[i][j] << " ";
            }
            cout << endl;
        }
    }else{
        // cout << "Yes" << endl;
        vector<int> a(q);
        for(int i = 0; i < q; i++){
            if(i >= q/2) a[i] = -q/2+i+1;
            else a[i] = -q/2+i;
        }
        vector<vector<int>> ans(q, vector<int>(q));
        for(int i = 0; i < q/2; i++){
            for(int j = 0; j < q; j++){
                ans[i][(i+j)%q] = a[j]+i;
            }
        }
        int cnt = q/2 - 1;
        for(int i = q/2; i < q; i++){
            for(int j = 0; j < q; j++){
                ans[i][(i+j)%q] = a[j] - cnt;
            }
            cnt--;
        }
        for(int i = 0; i < q; i++){
            for(int j = 0; j < q; j++){
                // cout << ans[i][j] << " ";
                if(ans[i][j] == ans[j][i] and i != j){
                    cout << "Error" << q << " " << i << " " << j << endl;
                }
            }
            // cout << endl;
        }
    }
    }
}
