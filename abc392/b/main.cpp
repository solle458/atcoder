#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    set<int> a;
    for(int i = 0; i < m; i++){
        int b;
        cin >> b;
        a.insert(b);
    }
    vector<int> ans;
    for(int i = 1; i <= n; i++)if(a.find(i) == a.end())ans.push_back(i);
    cout << ans.size() << endl;
    for(int i = 0; i < ans.size(); i++)cout << ans[i] << (i == ans.size()-1 ? "\n" : " ");
}
