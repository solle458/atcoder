#include <iostream>
#include <queue>

using namespace std;

int main(){
    int Q;
    cin >> Q;
    priority_queue<int, vector<int>, greater<int>> pq;
    queue<int> q;
    while(Q--){
        int v;
        cin >> v;
        if(v == 1){
            int x;
            cin >> x;
            q.push(x);
        }else if(v == 2){
            if(!pq.empty()){
                cout << pq.top() << endl;
                pq.pop();
            }else{
                cout << q.front() << endl;
                q.pop();
            }
        }else{
            while(!q.empty()){
                pq.push(q.front());
                q.pop();
            }
        }
    }
}
