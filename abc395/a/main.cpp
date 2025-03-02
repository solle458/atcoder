#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x : a) cin >> x;
    for(int i = 0; i < n-1; i++)if(a[i] >= a[i+1]){
        cout << "No" << endl;
        return 0;
    }
    cout << "Yes" << endl;
}
