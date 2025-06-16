#include <iostream>
#include <numeric>
#include <deque>

using namespace std;

int main(){
    long long n, top = 0;
    int q;
    cin >> n >> q;
    deque<long long> a(n);
    iota(a.begin(), a.end(), 1);
    for(int i = 0; i < q; i++){
        long long x;
        cin >> x;
        if(x == 1){
            long long p, v;
            cin >> p >> v;
            a[(top + p - 1) % n] = v;
        }else if(x == 2){
            long long p;
            cin >> p;
            cout << a[(top + p - 1) % n] << endl;
        }else{
            long long k;
            cin >> k;
            top = (top + k) % n;
        }
    }
}
