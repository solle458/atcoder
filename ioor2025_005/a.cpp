#include <iostream>

using namespace std;

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < 4; i++)if((n+i)%4 == 0)cout << n+i << endl;
}
