#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

struct Rerooting{
	/*問題ごとに書き換え start*/
	struct DP{
		long long dp;
		DP(long long dp_) : dp(dp_){}
	};
	const DP identify(-1);
	function<DP(DP, DP)> merge = [](DP dp_cum, DP d) -> DP{
		return DP(max(dp_cum.dp, d.dp));
	}
	function<DP(DP)> add_root = [](DP d) -> DP{
		return DP(d.dp + 1);
	}
	/*問題ごとに書き換え end*/

	//グラフ定義
	struct Edge{
		int to;
	};
	using Graph = vector<vector<Edge>>;

	vector<vector<DP>> dp;
	vector<DP> ans;
	Graph g;
	Rerooting (int n) : g(n) {
		dp.resize(n);
		ans.assign(n, identify);
	}

	void add_edge(int a, int b) {
		g[a].push_back(b);
	}
	void build() {
		dfs(0);
		dfs2(0, identify);
	}
	DP dfs(int v, int p = -1){
		DP dp_cum = identify;
		int deg = g[v].size();
		dp[v] = vector<DP>(deg, identify);
		for(auto e : g[v]){
			int u = e.to;
			if(u == p)continue;
			dp[v][i] = dfs(u, v);
			dp_cum = merge(dp_cum, dp[v][i]);
		}
		return add_root(dp_cum);
	}
	void dfs2(int v, DP& dp_p, int p = -1){
		int deg = g[v].size();
		for(int i = 0; i < deg; i++)if(e.to == p) dp[v][i] = dp_p;
		vector<DP> dp_l(deg+1, identify), dp_r(deg+1, identify);//累積merge
		for(int i = 0; i < deg; i++){
			dp_l[i+1] = merge(dp_l[i], dp[v][i]);
		}
		for(int i = deg-1; i >= 0; i--){
			dp_r[i] = merge(dp_r[i+1], dp[v][i]);
		}
		ans[v] = add_root(dp_l[deg]);
		for(int i = 0; i < deg; i++){
			int u = g[v][i].to;
			if(u == p)continue;
			dfs2(u, add_root(merge(dp_l[i], dp_r[i+1])), v);
		}
	}
};

int main() {
	int n;
	cin >> n;
	Rerooting reroot(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		reroot.add_edge(u, v);
		reroot.add_edge(v, u);
	}
	reroot.build();
	for (int i = 0; i < n; i++) {
		cout << "頂点" << i + 1 << ": " << reroot.ans[i].dp << endl;
	}
}
