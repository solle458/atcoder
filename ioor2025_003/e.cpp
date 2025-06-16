#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
typedef long long ll;

ll ans = 0;
ll n,x;
vector<vector<ll>>a;
void dfs(ll pos,ll seki){
    if(pos==n){
        if(seki == x)ans++;
        return;
    }
    for(ll c:a[pos]){
        if(seki>x/c)continue;
        dfs(pos+1,seki*c);
    }
}

signed main(){
    cin>>n>>x;
    a.resize(n);
    for(ll i=0;i<=n-1;i++){
        ll L;cin>>L;
        a[i].resize(L);
        for(ll j=0;j<=L-1;j++)cin>>a[i][j];
    }
    dfs(0,1);
    cout<<ans<<endl;
    return 0;
}
