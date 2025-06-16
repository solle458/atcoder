#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main(){
    int n, r;
    while(cin >> n >> r, (n != 0 and r != 0)){
        vector<int> ans(n);
        iota(ans.begin(), ans.end(), 1);
        for(int i = 0; i < r; i++){
            // for(auto a : ans)cerr << a << " ";
            // cerr << endl;
            int p, c;
            cin >> p >> c;
            vector<int> cp(n);
            int k = 0;
            for(int j = 0; j < n; j++){
                if(n-p-c+1 <= j and j <= n-p)continue;
                cp[k] = ans[j];
                k++;
            }
            for(int j = 0; j < c; j++){
                cp[n-1-c+1+j] = ans[n-p-c+1+j];
            }
            ans = cp;
        }
        cout << ans[n-1] << endl;
    }
}
