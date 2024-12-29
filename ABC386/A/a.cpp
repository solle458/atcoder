#include <iostream>
#include <map>

using namespace std;

int main(){
  map<int, int> mp;
  for(int i = 0; i < 4; i++){
    int a;
    cin >> a;
    mp[a]++;
  }
  if(mp.size() == 2)cout << "Yes" << endl;
  else cout << "No" << endl;
}
