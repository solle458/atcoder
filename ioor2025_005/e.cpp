#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main(){
    int n, k, r, s, p;
    string t;
    cin >> n >> k >> r >> s >> p >> t;
    vector<string> modK(k);
    for(int i = 0; i < n; i++)modK[i % k] += t[i];
    
}
