#include <iostream>

using namespace std;

int main(){
    int n;
    cin >> n;
    string s;
    int l = 0;
    for(int i = 0; i < n; i++){
        char a;
        cin >> a;
        if(a == '('){
            l++;
            s.push_back(a);
        }else if(a == ')'){
            if(l > 0){
                l--;
                while(s.back() != '(')s.pop_back();
                s.pop_back();
            }else{
                s.push_back(a);
            }
        }else{
            s.push_back(a);
        }
    }
    cout << s << endl;
}
