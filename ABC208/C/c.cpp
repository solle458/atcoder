#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
  int n;
  long long k;
  cin >> n >> k;
  vector<pair<int, int>> p(n);
  for(int i = 0; i < n; i++){
    cin >> p[i].first;
    p[i].second = i;
  }
  sort(p.begin(), p.end());
  long long b = k%n;
  vector<long long> ans(n);
  for(int i = 0; i < n; i++){
    if(i < b) ans[p[i].second] = k/n + 1;
    else ans[p[i].second] = k/n;
  }
  for(int i = 0; i < n; i++)cout << ans[i] << endl;
}

