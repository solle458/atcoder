#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for(auto& ai : a)cin >> ai;
    for(auto& bi : b)cin >> bi;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    
}
