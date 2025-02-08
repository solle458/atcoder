#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> p(n), q(n), ans(n);
    for(int i = 0; i < n; i++)cin >> p[i];
    for(int i = 0; i < n; i++)cin >> q[i];
    for(int i = 0; i < n; i++)ans[q[i]-1] = p[i]-1;
    for(int i = 0; i < n; i++)cout << q[ans[i]] << (i == n-1 ? "\n" : " ");
}
