#include <iostream>
#include <vector>

using namespace std;

int main(){
    int miss = 0;
    vector<int> a(5), ans = {1, 2, 3, 4, 5};
    for(int i = 0; i < 5; i++)cin >> a[i];
    for(int i = 0; i < 4; i++)if(a[i]-1 != i)swap(a[i], a[i+1]), miss++;
    if(miss == 1 and ans == a)cout << "Yes" << endl;
    else cout << "No" << endl;
}
