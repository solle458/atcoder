#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<string> a(n), b(n);
    for(int i = 0; i < n; i++)cin >> a[i];
    for(int i = 0; i < n; i++)cin >> b[i];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(a[i][j] != b[i][j]){
                cout << i+1 << " "  << j+1 << endl;
                return 0;
            }
        }
    }
}
