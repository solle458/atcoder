#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main(){
  long long l, r;
  cin >> l >> r;

  auto f = [&](long long x) -> long long{
    if(x < 10)return 0;
    string s = to_string(x);
    int sz = s.size();
    long long ret = 0;
    for(int i = 1; i <= sz-2; i++){
      for(int j = 1; j <= 9; j++){
        ret += powl(j, sz-1-i);
      }
    }

    vector<vector<vector<long long>>> dp(sz+1, vector<vector<long long>>(s[0] - '0' + 1, vector<long long>(2, 0ll)));
    for(int i = 1; i < s[0] - '0'; i++) dp[1][i][true] = 1;
    dp[1][s[0] - '0'][false] = 1;
    for(int i = 1; i < sz; i++){
      for(int mx = 1; mx <= s[0] - '0'; mx++){
        for(int less = 0; less <= 1; less++){
          for(int d = 0; d <= (less ? mx-1 : min(mx-1, s[i] - '0')); d++){
            dp[i+1][mx][less | (d < s[i] - '0')] += dp[i][mx][less];
          }
        }
      }
    }
    for(int i = 1; i <= s[0] - '0'; i++){
      ret += dp[sz][i][true];
      ret += dp[sz][i][false];
    }
    return ret;
  };

  cout << f(r) - f(l-1) << endl;
}
