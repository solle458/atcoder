#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

int main(){
  int h, w;
  pair<int, int> start;
  long long x;
  cin >> h >> w >> x >> start.first >> start.second;
  vector<vector<long long>> s(h, vector<long long>(w));
  for(int i = 0; i < h; i++)for(int j = 0; j < w; j++) cin >> s[i][j];
  start.first--;
  start.second--;
  priority_queue<pair<long long, pair<int, int>>, vector<pair<long long, pair<int, int>>>, greater<pair<long long, pair<int, int>>>> pq;
  long long t = s[start.first][start.second];
  vector<vector<bool>> dist(h, vector<bool>(w, false));
  pq.push({0, {start.first, start.second}});
  while(!pq.empty()){
    auto now = pq.top();
    pq.pop();
    int ny = now.second.first, nx = now.second.second;
    if(dist[ny][nx])continue;
    if((double)t/x <= now.first)continue;
    dist[ny][nx] = true;
    t += now.first;
    for(int i = 0; i < 4; i++){
      int y = ny + dy[i], x = nx + dx[i];
      if(y < 0 or h <= y or x < 0 or w <= x)continue;
      if(dist[y][x])continue;
      pq.push({s[y][x], {y, x}});
    }
  }
  cout << t << endl;
}
