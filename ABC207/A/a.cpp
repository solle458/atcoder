#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
  vector<int> a(3);
  for(auto &x : a)cin >> x;
  sort(a.begin(), a.end());
  cout << a[1]+a[2] << endl;
}
