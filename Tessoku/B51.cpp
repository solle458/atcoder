#include <iostream>
#include <stack>

using namespace std;

int main(){
  string s;
  cin >> s;
  stack<pair<char, int>> st;
  for(int i = 0; i < s.size(); i++){
    if(st.empty()){
      st.push({s[i], i+1});
      continue;
    }
    char c = st.top().first;
    int n = st.top().second;
    if(s[i] == ')'){
      cout << n << " " << i+1 << endl;
      st.pop();
    }else st.push({s[i], i+1});
  }
}
