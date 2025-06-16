#include <iostream>
#include <vector>
#include <map>

using namespace std;

map<long long, long long> mp;

long long dfs(long long p){
    if(mp.count(p)){
        return mp[p];
    }
    if(p < 2){
        return mp[p] = 0;
    }
    long long res = 0;
    if(p % 2 == 0){
        res += dfs(p / 2) * 2;
    }else{
        res += dfs((p-1)/2);
        res += dfs((p+1)/2);
    }
    return mp[p] = res + p;
}

int main(){
    long long n;
    cin >> n;
    cout << dfs(n) << endl;
}
