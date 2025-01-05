#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> a(n), b(n);
    vector<double> l, u;
    for(int i = 0; i < n; i++) cin >> a[i] >> b[i];
    for(int i = 0; i < n; i++){
        if(b[i] == y and a[i] < x){
            cout << "No" << endl;
            return 0;
        }
        double t = (double)(a[i]-x)/(y-b[i]);
        if(t < 0) continue;
        if(a[i] > x) u.push_back(t);
        else if(a[i] < x) l.push_back(t);
    }
    sort(l.begin(), l.end());
    sort(u.begin(), u.end());
    if(!l.empty() and !u.empty() and l.back() > u.front()){
        cout << "No" << endl;
        return 0;
    }else{
        cout << "Yes" << endl;
        return 0;
    }
}
