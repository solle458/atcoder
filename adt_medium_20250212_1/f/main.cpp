#include <iostream>
#include <vector>

using namespace std;

vector<int> ans;
vector<vector<int>> a;
vector<bool> visited;

int dfs(int v){
  visited[v] = true;
  int now = a[v][0];
  if(visited[now]){
    return now;
  }
  ans.push_back(now);
  int result = dfs(now);
  if(result != -1)return result;
  ans.pop_back();
  return -1;
}

int main(){
  int n;
  cin >> n;
  a.resize(n);
  visited.resize(n);
  for(int i = 0; i < n; i++){
    int v;
    cin >> v;
    a[i].push_back(v-1);
  }
  for(int i = 0; i < n; i++){
    ans.push_back(i);
    int result = dfs(i);
    if(result != -1){
      int loop = ans.size(), idx;
      for(int j = 0; j < loop; j++){
        if(ans[j] == result)idx = j;
      }
      cout << ans.size() - idx << endl;
      for(int j = idx; j < loop; j++)cout << ans[j]+1 << (j == loop-1 ? "\n" : " ");
      return 0;
    }
    ans.pop_back();
  }
}
