#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    int a, b;
    cin >> a >> b;
    cout << ((min(a, b)+1 == max(a, b) or (min(a, b) == 1 and max(a, b) == 10)) ? "Yes" : "No") << endl;
}
