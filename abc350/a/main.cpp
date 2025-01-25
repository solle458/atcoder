#include <iostream>

using namespace std;

int main(){
    string s, num;
    cin >> s;
    num = s.substr(3, 3);
    if("001" <= num and num <= "349" and num != "316")cout << "Yes" << endl;
    else cout << "No" << endl; 
}
