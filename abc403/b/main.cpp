#include <iostream>

using namespace std;

int main(){
    string t, u;
    cin >> t >> u;
    int n = t.size(), m = u.size();
    for(int i = 0; i < n-m+1; i++){
        int cnt = 0;
        for(int j = 0; j < m; j++){
            if(t[i+j] != u[j]){
                if(t[i+j] == '?')cnt++;
                else{
                    cnt = 1e9;
                    break;
                }
            }
        }
        if(cnt <= 4){
            cout << "Yes" << endl;
            return 0;
        }
    }
    cout << "No" << endl;
}
