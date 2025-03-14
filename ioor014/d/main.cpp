#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main(){
    int n, k;
    cin >> n >> k;
    vector<long long> p(n);
    for(auto &x : p)cin >> x;
    priority_queue<long long, vector<long long>, greater<long long>> pq;
    for(int i = 0; i < k; i++)pq.push(p[i]);
    cout << pq.top() << endl;
    for(int i = k; i < n; i++){
        if(pq.top() < p[i]){
            pq.pop();
            pq.push(p[i]);
        }
        cout << pq.top() << endl;
    }
}
