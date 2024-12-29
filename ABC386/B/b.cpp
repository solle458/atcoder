#include <iostream>
#include <string>

using namespace std;

int main(){
  string s;
  cin >> s;
  int ans = 0;
  auto f = s.find("00");
  while(f != string::npos){
    ans++;
    s.erase(f, 2);
    f = s.find("00");
  }
  cout << ans + s.size() << endl;
}
