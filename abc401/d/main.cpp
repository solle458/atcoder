#include <iostream>
#include <vector>

using namespace std;

vector<pair<char, int>> runLength(const string& s) {
    vector<pair<char, int>> result;
    int n = s.size();
    if (n == 0) return result;

    char prev = s[0];
    int count = 1;

    for (int i = 1; i < n; i++) {
        if (s[i] == prev) {
            count++;
        } else {
            result.emplace_back(prev, count);
            prev = s[i];
            count = 1;
        }
    }
    result.emplace_back(prev, count);

    return result;
}

int main(){
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    for(int i = 0; i < n-1; i++){
        if(s[i] == 'o' and s[i+1] == '?') s[i+1] = '.';
        else if(s[i] == '?' and s[i+1] == 'o') s[i] = '.';
    }
    vector<pair<char, int>> rl = runLength(s);
    int sumQ = 0, sumO = 0;
    for(auto &p : rl){
        if(p.first == 'o') sumO += p.second;
        else if(p.first == '?'){
            if(p.second % 2 == 0){
                sumQ += p.second/2;
            }else{
                sumQ += p.second/2+1;
            }
        }
    }
    if(k-sumO == 0){
        for(int i = 0; i < n; i++)if(s[i] == '?')s[i] = '.';
        cout << s << endl;
    }else if(sumQ == k-sumO){
        int idx = 0;
        for(auto &p : rl){
            idx += p.second;
            if(p.first == '?' and p.second%2 == 1){
                for(int i = 0; i < p.second; i++){
                    s[idx-1-i] = (i%2 == 0) ? 'o' : '.';
                }
            }
        }
        cout << s << endl;
    }else cout << s << endl;
}
