#include <iostream>

using namespace std;

int main(){
  int n;
  char c1, c2;
  string s;
  cin >> n >> c1 >> c2 >> s;
  for(auto c : s)cout << (c == c1 ? c1 : c2);
  cout << endl;
}
