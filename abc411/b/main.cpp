#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n-1);
    for(int i = 0; i < n-1; i++)cin >> a[i];
    for(int i = 0; i < n-1; i++){
        int sum = 0;
        for(int j = i; j < n-1; j++){
            sum += a[j];
            cout << sum << " ";
        }
        cout << endl;
    }
}
