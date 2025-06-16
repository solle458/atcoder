#include <iostream>
#include <cmath>
#include <algorithm>
#include <cfloat>
#include <stack>
#include <queue>
#include <vector>
typedef long long int ll;
#define BIG_NUM 2000000000
#define MOD 1000000007
#define EPS 0.000001
using namespace std;

int ans,count_MAX;
int P,Q,Limit,common;

void recursive(int bunshi,int bunbo,int pre_add_bunbo,int bunbo_sum,int count){

	if(Q*bunshi == P*bunbo){
		ans++;
		return;
	}
	if(count == count_MAX)return;

	if(Q*bunshi > P*bunbo)return;

	int next_bunshi,next_bunbo;

	for(int i = pre_add_bunbo; bunbo_sum*i <= Limit; i++){

		next_bunshi = bunshi*i+bunbo;
		next_bunbo = bunbo*i;

		recursive(next_bunshi,next_bunbo,i,bunbo_sum*i,count+1);
	}
}

int main(){

	while(true){
        cin >> P >> Q >> Limit >> count_MAX;
		if(P == 0 && Q == 0 && Limit == 0 && count_MAX == 0)break;

		ans = 0;

		recursive(0,1,0,1,0);

		cout << ans << endl;

	}

	return 0;
}
