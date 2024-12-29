#include <iostream>
#include <map>

using namespace std;

int main(){
  int Q; 
  cin >> Q;
  map<string, int> mp;
  for(int q = 0; q < Q; q++){
    int v, x;
    string s;
    cin >> v;
    if(v == 1){
      cin >> s >> x;
      mp[s] += x;
    }else if(v == 2){
      cin >> s;
      cout << mp[s] << endl;
    }
  }
}
