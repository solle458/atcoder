#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

vector<int> score(5);
map<int, vector<string>> mp;

void solve(int now, int sum, string s){
  if(now == 5) return;
  char c = 'A'+now;
  mp[sum+score[now]].push_back(s+c);
  solve(now+1, sum+score[now], s+c);
  solve(now+1, sum, s);
}


int main(){
  for(auto &x : score) cin >> x;
  solve(0, 0, "");
  for(auto i = mp.rbegin(); i != mp.rend(); i++){
    vector<string> ans = i->second;
    sort(ans.begin(), ans.end());
    for(auto out : ans)cout << out << endl;
  }
}
