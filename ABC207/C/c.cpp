#include <iostream>
#include <vector>

using namespace std;

int main(){
  int n;
  cin >> n;
  vector<pair<double, double>> sec;
  for(int i = 0; i < n; i++){
    int t;
    double l, r;
    cin >> t >> l >> r;
    if(t == 2)r -= 0.1;
    else if(t == 3)l += 0.1;
    else if(t == 4){
      l += 0.1;
      r -= 0.1;
    }
    sec.push_back({l, r});
  } 
  int ans = 0;
  for(int i = 0; i < n; i++){
    for(int j = i+1; j < n; j++){
      if(sec[i].first <= sec[j].first and sec[j].first <= sec[i].second)ans++;
      else if(sec[i].first <= sec[j].second and sec[j].second <= sec[i].second)ans++;
      else if(sec[j].first <= sec[i].first and sec[i].first <= sec[j].second)ans++;
      else if(sec[j].first <= sec[i].second and sec[i].second <= sec[j].second)ans++;
    }
  }
  cout << ans << endl;
}
