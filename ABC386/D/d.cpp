#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

int main(){
  long long n, m;
  cin >> n >> m;
  set<pair<long long, long long>> w, b1, b2;
  for(int i = 0; i < m; i++){
    char c;
    long long x, y;
    cin >> x >> y >> c;
    if(c == 'W')w.insert({x, y});
    else{
      b1.insert({x, y});
      b2.insert({y, x});
    }
  }
  for(auto [x, y] : w){
    auto lb1 = b1.lower_bound({x, y});
    if(lb1 == b1.end())continue;
    int r = lb1->first, c = lb1->second;
    if(r >= x and c >= y){
      cout << "No" << endl;
      return 0;
    }
    auto lb2 = b2.lower_bound({y, x});
    if(lb2 == b2.end())continue;
    r = lb2->second, c = lb2->first;
    if(r >= x and c >= y){
      cout << "No" << endl;
      return 0;
    }
  }
  cout << "Yes" << endl;
}
