#include <iostream>
#include <vector>

using namespace std;

int main(){
  int n;
  cin >> n;
  int ans = 0;
  for(int i = 1; i <= 9; i++)for(int j = 1; j <= 9; j++)if(i*j != n) ans += i*j;
  cout << ans << endl;
}
