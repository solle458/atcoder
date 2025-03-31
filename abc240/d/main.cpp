#include <iostream>
#include <deque>

using namespace std;

int main(){
    int n, cnt = 0, sum = 0;
    cin >> n;
    deque<int> st, ch;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        sum++;
        if(st.empty()){
            st.push_back(a);
            ch.push_back(1);
        }else{
            if(st.back() == a){
                ch.back()++;
            }else{
                st.push_back(a);
                ch.push_back(1);
            }
        }
        if(ch.back() == st.back()){
            sum -= ch.back();
            st.pop_back();
            ch.pop_back();
        }
        cout << sum << endl;
    }
}
