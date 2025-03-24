#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x: a) cin >> x;
    int cost = 1e9;
    for(int i = -100; i <= 100; i++){
        int c = 0;
        for(auto &x : a) c += (x - i) * (x - i);
        if(c < cost) cost = c;
    }
    cout << cost << endl;
}
