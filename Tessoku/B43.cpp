#include <iostream>
#include <map>

using namespace std;

int main(){
  int n, m;
  cin >> n >> m;
  map<int, int> mp;
  for(int i = 0; i < m; i++){
    int a;
    cin >> a;
    mp[a]++;
  }
  for(int i = 1; i <= n; i++) cout << m - mp[i] << endl;
}
