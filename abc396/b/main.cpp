#include <iostream>
#include <stack>
using namespace std;

int main(){
    stack<int> s;
    for(int i = 0; i < 100; i++)s.push(0);
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        int v, x;
        cin >> v;
        if(v == 1){
            cin >> x;
            s.push(x);
        }else{
            cout << s.top() << endl;
            s.pop();
        }
    }
}
