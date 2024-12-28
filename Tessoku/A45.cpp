#include <iostream>
#include <vector>

using namespace std;

int main(){
  int n;
  char c;
  string s;
  cin >> n >> c >> s;
  int score = 0;
  for(auto c : s){
    if(c == 'B')score++;
    else if(c == 'R')score += 2;
  }
  if(score%3 == 0 and c == 'W')cout << "Yes" << endl;
  else if(score%3 == 1 and c == 'B')cout << "Yes" << endl;
  else if(score%3 == 2 and c == 'R')cout << "Yes" << endl;
  else cout << "No" << endl;
}
