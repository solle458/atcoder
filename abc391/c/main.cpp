#include <iostream>
#include <map>

using namespace std;

int main(){
    int n, q;
    cin >> n >> q;
    map<int, int> bird, home;
    for(int i = 1; i <= n; i++){
        bird[i] = i;
        home[i]++;
    }
    int ans = 0;
    while(q--){
        int x, p, h;
        cin >> x;
        if(x == 1){
            cin >> p >> h;
            int tmp = bird[p];
            bird[p] = h;
            if(home[tmp] == 2)ans--;
            home[tmp]--;
            if(home[h] == 1)ans++;
            home[h]++;
        }else{
            cout << ans << endl;
        }
    }
}
