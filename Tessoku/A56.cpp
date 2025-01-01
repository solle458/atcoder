#include <iostream>
#include <vector>

using namespace std;

long long mod=1e9+7;

int main(){
  long long n, q;
  string s;
  cin >> n >> q >> s;
  vector<long long> p(n+1,1), h(n+1,0);
  for(int i = 1; i <= n; i++){
    p[i] = (p[i-1]*100ll)%mod;
    h[i] = (100ll*h[i-1] + s[i-1]-'a' + 1)%mod;
  }
  long long a, b, c, d;
  while(cin >> a >> b >> c >> d){
    long long x=(h[b]-h[a-1]*p[b-a+1]%mod+mod)%mod;
    long long y=(h[d]-h[c-1]*p[d-c+1]%mod+mod)%mod;
    cout << (x == y ? "Yes" : "No") << endl;
  }
}
