#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
  int n;
  long long s, sumA = 0;
  cin >> n >> s;
  vector<long long> a(n), sum(2*n+1, 0);
  for(auto &x : a){
    cin >> x;
    sumA += x;
  }
  for(int i = 0; i < 2*n; i++) sum[i+1] = sum[i] + a[i%n];
  s %= sumA;
  if(s == 0){
    cout << "Yes" << endl;
    return 0;
  }
  for(int i = 0; i < n; i++){
    long long l = i, r = i+n;
    while(r-l > 1){
      long long mid = (r+l)/2;
      if(sum[mid]-sum[i] > s) r = mid;
      else l = mid;
    }
    if(sum[l] - sum[i] == s){
      cout << "Yes" << endl;
      return 0;
    }
  }
  cout << "No" << endl;
}
