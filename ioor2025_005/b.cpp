#include <iostream>
#include <vector>

using namespace std;

int main(){
    string s;
    cin >> s;
    vector<int> num(4);
    for(int i = 0; i < 4; i++) num[i] = s[i] - '0';
    for(int i = 0; i < 2; i++){
        string op;
        if(i == 0) op+= '+';
        else op += '-';
        for(int j = 0; j < 2; j++){
            if(j == 0) op += '+';
            else op += '-';
            for(int k = 0; k < 2; k++){
                if(k == 0) op += '+';
                else op += '-';
                int result = num[0];
                for(int l = 1; l < 4; l++){
                    if(op[l-1] == '+') result += num[l];
                    else result -= num[l];
                }
                if(result == 7){
                    cout << num[0] << op[0] << num[1] << op[1] << num[2] << op[2] << num[3] << "=7" << endl;
                    return 0;
                }
                op.pop_back();
            }
            op.pop_back();
        }
        op.pop_back();
    }
}
