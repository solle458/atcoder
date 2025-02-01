#include <iostream>
#include <map>

using namespace std;

int main(){
    map<string, string> m;
    m["N"] = "S";
    m["S"] = "N";
    m["E"] = "W";
    m["W"] = "E";
    m["NE"] = "SW";
    m["NW"] = "SE";
    m["SE"] = "NW";
    m["SW"] = "NE";
    string s;
    cin >> s;
    cout << m[s] << endl;
}
