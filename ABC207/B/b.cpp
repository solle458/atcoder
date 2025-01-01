#include <iostream>

using namespace std;

int main(){
  long long a, b, c, d;
  cin >> a >> b >> c >> d;
  long long ans = 0, r = 0;
  while(a > d*r){
    ans++;
    r += c;
    a += b;
    if(ans == 1e6){
      cout << -1 << endl;
      return 0;
    }
  }
  cout << ans << endl;
}
