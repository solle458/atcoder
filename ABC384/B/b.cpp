#include <iostream>
#include <vector>

using namespace std;

int main(){
  int n, r;
  cin >> n >> r;
  for(int i = 0; i < n; i++){
    int d, a;
    cin >> d >> a;
    if(d == 1 and 1600 <= r and r <= 2799) r += a;
    if(d == 2 and 1200 <= r and r <= 2399) r += a;
  }
  cout << r << endl;
}
