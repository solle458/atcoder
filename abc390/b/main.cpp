#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<long double> a(n);
    for(auto &x : a)cin >> x;
    long double c = a[1]/a[0];
    for(int i = 2; i < n; i++)if(a[i]/a[i-1] != c){
        cout << "No" << endl; 
        return 0;
    }
    cout << "Yes" << endl;
}
