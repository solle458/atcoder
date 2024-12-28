#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n;
vector<long long> a, b;

long long solve(bool front, bool back){
  long long sum = 0;
  for(int i = 0; i < n; i++){
    long long card = 0;
    if(front)card += a[i];
    else card += -a[i];
    if(back)card += b[i];
    else card += -b[i];
    if(card >= 0)sum += card;
  }
  return sum;
}

int main(){
  cin >> n;
  a.resize(n);
  b.resize(n);
  for(int i = 0; i < n; i++)cin >> a[i] >> b[i];
  long long ans = -1e18;
  ans = max(ans, solve(true, true));
  ans = max(ans, solve(true, false));
  ans = max(ans, solve(false, true));
  ans = max(ans, solve(false, false));
  cout << ans << endl;
}
