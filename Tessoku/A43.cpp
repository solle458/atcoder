#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
  int n;
  long long l;
  cin >> n >> l;
  vector<pair<long long, char>> ab(n);
  for(auto &[a, b] : ab)cin >> a >> b;
  long long ans = 0;
  for(auto [a, b] : ab){
    if(b == 'E')ans = max(ans, l-a);
    else ans = max(ans, a);
  }
  cout << ans << endl;
}
