#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, p;
    while (cin >> n >> p) {
        if (n == 0 && p == 0) break;
        int have = 0, idx = 0;
        vector<int> a(n, 0);
        while (true){
            if(p == 0 and have == 1) break;
            if(p > 0){
                if(a[idx] == 0) have++;
                a[idx]++;
                p--;
                idx = (idx + 1) % n;
            }else{
                if(a[idx] == 0){
                    idx = (idx + 1) % n;
                    continue;
                }
                p += a[idx];
                a[idx] = 0;
                have--;
                idx = (idx + 1) % n;
            }
        }
        for(int i = 0; i < n; i++)if(a[i] != 0) cout << i << endl;
    }
}
