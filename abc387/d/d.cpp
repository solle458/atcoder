#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};

int main(){
  int h, w;
  cin >> h >> w;
  vector<string> s(h);
  pair<int, int> start, goal;
  for(int i = 0; i < h; i++){
    cin >> s[i];
    for(int j = 0; j < w; j++){
      if(s[i][j] == 'S') start = {i, j};
      else if(s[i][j] == 'G') goal = {i, j};
    }
  }
  vector<vector<int>> dist1(h, vector<int>(w, 1e9)), dist2(h, vector<int>(w, 1e9));
  queue<pair<pair<int, int>, int>> q1, q2;
  q1.push({start, 0});
  q2.push({start, 1});
  dist1[start.first][start.second] = 0;
  dist2[start.first][start.second] = 0;
  while(!q1.empty()){
    pair<int, int> p = q1.front().first;
    int y = p.first, x = p.second, d = q1.front().second;
    q1.pop();
    int b, e;
    if(d == 0){
      b = 2;
      e = 4;
    }else{
      b = 0;
      e = 2;
    }
    for(int i = b; i < e; i++){
      int ny = y+dy[i], nx = x+dx[i];
      if(ny < 0 or h <= ny or nx < 0 or w <= nx)continue;
      if(dist1[ny][nx] <= dist1[y][x]+1)continue;
      if(s[ny][nx] == '#')continue;
      q1.push({{ny, nx}, (d+1)%2});
      dist1[ny][nx] = dist1[y][x]+1;
    }
  }
  while(!q2.empty()){
    pair<int, int> p = q2.front().first;
    int y = p.first, x = p.second, d = q2.front().second;
    q2.pop();
    int b, e;
    if(d == 0){
      b = 2;
      e = 4;
    }else{
      b = 0;
      e = 2;
    }
    for(int i = b; i < e; i++){
      int ny = y+dy[i], nx = x+dx[i];
      if(ny < 0 or h <= ny or nx < 0 or w <= nx)continue;
      if(dist2[ny][nx] <= dist2[y][x]+1)continue;
      if(s[ny][nx] == '#')continue;
      q2.push({{ny, nx}, (d+1)%2});
      dist2[ny][nx] = dist2[y][x]+1;
    }
  }
  int ans = min(dist1[goal.first][goal.second], dist2[goal.first][goal.second]);
  if(ans == 1e9)ans = -1;
  cout << ans << endl;
}
