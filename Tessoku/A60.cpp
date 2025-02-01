#include <iostream>
#include <stack>

using namespace std;

int main(){
    int n, a;
    stack<pair<int,int>>s;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> a;
        while(!s.empty() and s.top().second <= a) s.pop();
        if(s.empty()) cout << -1 << " ";
        else cout << s.top().first+1 << " ";
        s.push({i, a});
    }
    cout << endl;
}
