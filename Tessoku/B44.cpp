#include <iostream>
#include <vector>

using namespace std;

int main(){
  int n;
  cin >> n;
  vector<vector<int>> a(n, vector<int>(n));
  for(int i = 0; i < n; i++)for(int j = 0; j < n; j++)cin >> a[i][j];
  int q;
  cin >> q;
  for(int i = 0; i < q; i++){
    int v, x, y;
    cin >> v >> x >> y;
    x--;
    y--;
    if(v == 1)swap(a[x], a[y]);
    else cout << a[x][y] << endl;
  }
}
