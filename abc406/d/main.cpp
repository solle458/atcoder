#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main(){
    int h, w, n;
    cin >> h >> w >> n;
    vector<set<int>> setX(h), setY(w);
    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        setX[x-1].insert(y-1);
        setY[y-1].insert(x-1);
    }
    int Q;
    cin >> Q;
    vector<bool> usedX(h, false), usedY(w, false);
    for(int i = 0; i < Q; i++){
        int q, x, y;
        cin >> q;
        if(q == 1){
            cin >> x;
            if(usedX[x-1]){
                cout << 0 << endl;
                continue;
            }
            usedX[x-1] = true;
            cout << setX[x-1].size() << endl;
            for(auto it = setX[x-1].begin(); it != setX[x-1].end(); it++){
                setY[*it].erase(x-1);
            }
        } else {
            cin >> y;
            if(usedY[y-1]){
                cout << 0 << endl;
                continue;
            }
            usedY[y-1] = true;
            cout << setY[y-1].size() << endl;
            for(auto it = setY[y-1].begin(); it != setY[y-1].end(); it++){
                setX[*it].erase(y-1);
            }
        }
    }
}
