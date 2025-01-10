#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<bool> b(n+1, false);
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        b[a] = true;
    }
    for(int i = 1; i <= n; i++)if(!b[i]){
        cout << "No" << endl;
        return 0;
    }
    cout << "Yes" << endl;
}