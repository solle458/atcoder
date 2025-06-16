#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(){
    int n, t;
    cin >> n >> t;
    vector<long long> a(t), b(t), sum(n, 0);
    map<long long, long long> m;
    m[0] = n;
    for(int i = 0; i < t; i++){
        cin >> a[i] >> b[i];
        a[i]--;
        m[sum[a[i]]]--;
        if(m[sum[a[i]]] == 0) m.erase(sum[a[i]]);
        sum[a[i]] += b[i];
        m[sum[a[i]]]++;
        cout << m.size() << endl;
    }
}
