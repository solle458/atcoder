#include <iostream>

using namespace std;

int main(){
  int a, b;
  cin >> a >> b;
  if(b < a-1)cout << 0 << endl;
  else cout << b - (a-1) << endl;
}
