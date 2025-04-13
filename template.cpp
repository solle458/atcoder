#include<iostream>
#include<iomanip>
#include<sstream>
#include<string>
#include<vector>
#include<algorithm>
#include<numeric>
#include<cmath>
#include<map>
#include<set>
#include<list>
#include<stack>
#include<queue>
#include<deque>
#include<bitset>
#include<cctype>
#include<chrono>
#include<atcoder/all>

using namespace std;
using namespace atcoder;

#define ll long long
#define ull unsigned long long
#define rep(i, start, end) for(int i = start; i < end; i++)
#define rep2(i, start, end) for(int i = start; i <= end; i++)
#define rrep(i, start, end) for(int i = start; i >= end; i--)
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define P pair<int, int>
#define Pll pair<ll, ll>

template<class T> bool chmin(T &a, T b)
{
    if(a>b){
      a=b;
      return true;
    }else{
      return false;
    }
}

template<class T> bool chmax(T &a, T b)
{
    if(a<b){
      a=b;
      return true;
    }else{
      return false;
    }
}

void YN(bool x)
{
    cout << (x?"Yes":"No") << endl;    
}

ll digit(ll n)
{
    ll digit_num = 0;
    while(n > 0){
        digit_num++;
        n /= 10;
    }
    return digit_num;
}

void T()
{
    cout << "Takahashi" << endl;
}

ll power_mod(ll n, ll k, ll mod)
{
    // ll mod = 998244353;
    ll result = 1;
    while (k > 0){
        if((k&1) == 1)result = (result*n)%mod;
        n = n*n%mod;
        k >>= 1;
    }
    return result;
}

int chc_n(char c)
{
    int a = c - 'a';
    return a;
}

char chn_c(int a)
{
    char c = a + 'a';
    return c;
}

ll ch_10num(string s, ll k)
{
    ll ans = 0;
    for(char x : s){
        ans *= k;
        ans += x -'0';
        // cout << ans << endl;
    }
    return ans;
}

//first降順 firstが同値の場合second昇順
bool desc_asc(pair<int, int>& left, pair<int, int>& right) {
  if (left.first == right.first) {
    return left.second < right.second;
  } else {
    return right.first < left.first;
  }
}

//first昇順 firstが同値の場合second降順
bool asc_desc(pair<int, int>& left, pair<int, int>& right) {
  if (left.first == right.first) {
    return right.second < left.second;
  } else {
    return left.first  < right.first;
  }
}

ll gcd(ll a, ll b){
  if(a < b)swap(a, b);
  if(b == 0)return a;
  else return gcd(b, a%b);
}

ll lcm(ll a, ll b){
  if(a < b)swap(a, b);
  return (a/gcd(a, b))*b;
}

vector<ll> eratosthenes(ll num){
  vector<ll> prime;
  vector<bool> is_prime(num, true);
  is_prime[0] = is_prime[1] = false;
  for(ll i = 2; i <= num; i++){
    if(is_prime[i]){
      prime.push_back(i);
      for(ll j = 2*i; j <= num; j += i){
        is_prime[j] = false;
      }
    }
  }
  return prime;
}

ll combination(ll n, ll r, ll mod){
  if(mod == -1)mod = 1e9+7;
  ll result = 1;
  for(ll i = 1; i <= r; i++){
    result = result*(n-i+1)%mod;
    result = result*power_mod(i, mod-2, mod)%mod;
  }
  return result;
}

/* bitDP
    int n, m;
    cin >> n >> m; 
    vector<vector<int>> a(m+1, vector<int>(n+1));
    rep2(i, 1, m) rep2(j, 1, n) cin >> a[i][j];
    vector<vector<int>> dp(m+1, vector<int>(1<<n, inf));
    dp[0][0] = 0;
    rep2(i, 1, m){
      rep(j, 0, 1<<n){
        int already[n+1];
        rep2(k, 1, n){
          if(j & (1<<(k-1)))already[k] = 1;
          else already[k] = 0;
        }
        int v = 0;
        rep2(k, 1, n) if(already[k] == 1 or a[i][k])v += (1<<(k-1));
        chmin(dp[i][j], dp[i-1][j]);
        chmin(dp[i][v], dp[i-1][j]+1);
      }
    }
    if(dp[m][(1<<n)-1] == inf)cout << -1 << endl;
    else cout << dp[m][(1<<n)-1] << endl;
*/

const int inf = 1<<30;

const ll INF = 1ll<<60;

const int dx[9] = {-1, 0, 1, 0, 1, 1, -1, -1, 0}, dy[9] = {0, 1, 0, -1, 1, -1, 1, -1, 0};
const char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

struct edge{
    ll to, cost;
};

vector<ll> dijkstra(vector<vector<edge>>& g, int start, int cost){
    vector<ll> dist(g.size(), INF);
    dist[start] = cost;
    priority_queue<Pll, vector<Pll>, greater<Pll>> pq;
    pq.push({cost, start});
    while(!pq.empty()){
        Pll p = pq.top();pq.pop();
        ll v = p.second;
        if(dist[v] < p.first)continue;
        for(edge e : g[v]){
            if(chmin(dist[e.to], dist[v]+e.cost)){
                pq.push({dist[e.to], e.to});
            }
        }
    }
    return dist;
}

vector<pair<char, int>> runLength(const string& s) {
    vector<pair<char, int>> result;
    int n = s.size();
    if (n == 0) return result;

    char prev = s[0];
    int count = 1;

    for (int i = 1; i < n; i++) {
        if (s[i] == prev) {
            count++;
        } else {
            result.emplace_back(prev, count);
            prev = s[i];
            count = 1;
        }
    }
    result.emplace_back(prev, count);

    return result;
}

/*-------------------------------template-------------------------------*/
int main(){
}
