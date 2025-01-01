#include <iostream>
#include <map>

using namespace std;

int main(){
  int p;
  cin >> p;
  map<long long, int> coin;
  for(int i = 0; i < 10; i++){
    long long tmp = 1;
    for(int j = 1; j <= i+1; j++)tmp *= j;
    coin[tmp] = 100;
  }
  int ans = 0;
  for(auto m = coin.rbegin(); m != coin.rend(); m++){
    int sum = p/m->first;
    if(sum >= 100){
      ans += 100;
      p -= m->first*100;
    }else{
      ans += sum;
      p -= m->first*sum;
    }
  }
  cout << ans << endl;
}
