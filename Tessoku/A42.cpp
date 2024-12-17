#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
  int n, k;
  cin >> n >> k;
  vector<pair<int, int>> ab(n);
  for(auto &[a, b] : ab) cin >> a >> b;
  int ans = 0;
  for(int i = 1; i <= 100 ; i++){
    for(int j = 1; j <= 100; j++){
      int tmp = 0;
      for(auto [a, b] : ab) if(i <= a and a <= i+k and j <= b and b <= j+k) tmp++;
      ans = max(ans, tmp);
    }
  }
  cout << ans << endl;
}
