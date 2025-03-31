#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
	int h, w, k;
	cin >> h >> w >> k;
	vector<string> s(h);
	for(int i = 0; i < h; i++) cin >> s[i];
	int ans = 0;
	for(int i = 0; i < (1<<h); i++){
		int kk = k;
		kk -= __builtin_popcount(i);
		if(kk<0)continue;
		int sum = 0;
		vector<int> a(w);
		for(int j = 0; j < h; j++){
			if((i>>j)&1){
				sum += w;
				continue;
			}
			for(int l = 0; l < w; l++){
				if(s[j][l]=='#')sum++;
				else a[l]++;
			}
		}
		sort(a.rbegin(), a.rend());
		for(int j = 0; j < min((int)a.size(),kk); j++){
			sum += a[j];
		}
		ans = max(ans, sum);
	}
	cout << ans << endl;
}
