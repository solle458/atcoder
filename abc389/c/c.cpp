#include <iostream>
#include <deque>

using namespace std;

int main(){
    int Q;
    cin >> Q;
    long long p = 0;
    deque<long long> d;
    d.push_back(0);
    while(Q--){
        int q, l, k;
        cin >> q;
        if(q == 1){
            cin >> l;
            if(d.empty()) d.push_back(l);
            else d.push_back(l+d.back());
        }else if(q == 2){
            d.pop_front();
            if(!d.empty())p = d.front();
        }else{
            cin >> k;
            cout << d[k-1]-p << endl;
        }
    }
}
