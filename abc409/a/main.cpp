#include <iostream>

using namespace std;

int main(){
    int n;
    string t, a;
    cin >> n >> t >> a;
    for(int i = 0; i < n; i++)if(t[i] == a[i] and t[i] == 'o'){
        cout << "Yes" << endl;
        return 0;
    }
    cout << "No" << endl;
    return 0;
}
