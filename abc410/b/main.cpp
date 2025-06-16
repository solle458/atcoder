#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n, q;
    cin >> n >> q;
    vector<int> b(n, 0);
    for(int i = 0; i < q; i++){
        int x;
        cin >> x;
        if(x == 0){
            int idx = 0;
            for(int j = 0; j < n; j++){
                if(b[j] < b[idx]){
                    idx = j;
                }
            }
            b[idx]++;
            cout << idx + 1 << " ";
        }else{
            b[x - 1]++;
            cout << x << " ";
        }
    }
}
