#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    for(int i = 0; i < 20; i++)for(int j = 0; j < 20; j++)cout << min({i, 20 - 1 - i, j, 20 - 1 - j}) << (j == 19 ? '\n' : ' ');
}
