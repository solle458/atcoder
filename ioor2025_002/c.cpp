#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int main(){
    int n, k;
    cin >> n >> k;
    vector<int> a(n), sum(n+1, 0);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        sum[i+1] = sum[i] + (a[i]+1);
    }
    int sumK = sum[k];
    for(int i = k; i < n; i++){
        sumK = max(sumK, sum[i+1] - sum[i-k+1]);
    }
    cout << fixed << setprecision(16) << (double)sumK/2. << endl;
}
