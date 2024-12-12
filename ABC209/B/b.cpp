#include <iostream>
#include <vector>

using namespace std;

int main(){
  int n, x, ans = 0;
  cin >> n >> x;
  for(int i = 1; i <= n; i++){
    int a;
    cin >> a;
    if(i%2  == 0)ans += a-1;
    else ans += a;
  }
  if(ans <= x)cout << "Yes" << endl;
  else cout << "No" << endl;
}
