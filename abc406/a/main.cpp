#include <iostream>

using namespace std;

int main(){
    string a, b, c, d;
    cin >> a >> b >> c >> d;
    if(a.size() == 1) a = "0" + a;
    if(b.size() == 1) b = "0" + b;
    if(c.size() == 1) c = "0" + c;
    if(d.size() == 1) d = "0" + d;
    string s = a+b, t = c+d;
    if(s < t){
        cout << "No" << endl;
    }else{
        cout << "Yes" << endl;
    }
}
