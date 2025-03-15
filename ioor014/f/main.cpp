#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main(){
    string t;
    int n;
    cin >> t >> n;
    vector<vector<string>> s(n);
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        s[i].resize(a);
        for(int j = 0; j < a; j++) cin >> s[i][j];
    }
}
