#include <iostream>

using namespace std;

int main(){
  long long n, sum = 0, ans = 0;
  cin >> n;
  for(int i = 1; i <= 1e9; i++){
    sum += i;
    if(sum >= n){
      cout << i << endl;
      return 0;
    }
  }
}
