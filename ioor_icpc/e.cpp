#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cctype>
#include<cassert>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
#define BIG_NUM 2000000000
#define HUGE_NUM 4000000000000000000 //オーバーフローに注意
#define MOD 1000000007
#define EPS 0.000000001



#define SIZE 500005
#define MAX_DEPTH 105

struct Node{

	int value; //葉なら値あり
	char op; //■@:葉
};


int num_node;
char line[SIZE];
vector<int> V[MAX_DEPTH],children[SIZE];
int dp_min[SIZE],dp_max[SIZE],pre_min[SIZE],pre_max[SIZE];
int ans_min[SIZE],ans_max[SIZE];
Node nodes[SIZE];


int calc_E(int left,int right,int depth);
int calc_F(int left,int right,int depth);
int calc_NUM(int left,int right,int depth);


//ノード番号を返す
int calc_E(int left,int right,int depth){

	vector<int> vec;

	//深さdepthの、プラスまたは-を探す
	int L = lower_bound(V[depth].begin(),V[depth].end(),left)-V[depth].begin();
	int R = upper_bound(V[depth].begin(),V[depth].end(),right)-V[depth].begin();
	R--;

	int ind;

	if(L == V[depth].size()){ //演算子なし

		ind = calc_F(left,right,depth);

	}else{ //演算子あり

		for(int i = L; i <= R; i++){

			vec.push_back(V[depth][i]); //インデックス
		}

		if(depth == 0){ //■ルート

			ind = 0;

			nodes[0].op = line[vec[0]]; //■rootは+2個か-2個

			int a = calc_F(left,vec[0]-1,depth);
			int b = calc_F(vec[0]+1,vec[1]-1,depth);
			int c = calc_F(vec[1]+1,right,depth);

			children[0].push_back(a);
			children[0].push_back(b);
			children[0].push_back(c);

		}else{

			++num_node; //■■注意■■

			ind = num_node;
			nodes[ind].op = line[vec[0]];

			int a = calc_F(left,vec[0]-1,depth);
			int b = calc_F(vec[0]+1,right,depth);

			children[ind].push_back(a);
			children[ind].push_back(b);
		}
	}

	return ind;
}


int calc_F(int left,int right,int depth){

	if(line[left] >= '0' && line[left] <= '9'){

		return calc_NUM(left,right,depth);

	}else{ // line[left] == '('

		return calc_E(left+1,right-1,depth+1);
	}
}

int calc_NUM(int left,int right,int depth){

	++num_node;

	nodes[num_node].op = '@';
	nodes[num_node].value = line[left]-'0';

	int ret = num_node;

	return ret;
}

//■葉方向の最大値、最小値を計算
void dfs(int node){

	if(nodes[node].op == '@'){//葉

		dp_min[node] = nodes[node].value;
		dp_max[node] = nodes[node].value;

		return;
	}

	//節
	vector<int> vec;

	for(int i = 0; i < children[node].size(); i++){

		int child = children[node][i];

		dfs(child);
		vec.push_back(child);
	}

	if(nodes[node].op == '+'){

		int maxi = 0;
		int mini = 0;

		for(int i = 0; i < children[node].size(); i++){

			int child = children[node][i];

			maxi += dp_max[child]; //最大値は、各子の最大値の和
			mini += dp_min[child]; //最小値は、各子の最小値の和
		}

		dp_max[node] = maxi;
		dp_min[node] = mini;

	}else{ //nodes[node].op == '-'

		int maxi = -BIG_NUM;
		int mini = BIG_NUM;

		for(int i = 0; i < vec.size(); i++){

			int left = vec[i]; //左端のノード

			int tmp_maxi = dp_max[left];
			int tmp_mini = dp_min[left];


			for(int k = 0; k < vec.size(); k++){

				if(k == i)continue;

				tmp_maxi -= dp_min[vec[k]];
				tmp_mini -= dp_max[vec[k]];
			}

			maxi = max(maxi,tmp_maxi);
			mini = min(mini,tmp_mini);
		}

		dp_max[node] = maxi;
		dp_min[node] = mini;
	}
}

void dfs2(int node,int pre){

	if(node == 0){

		ans_min[node] = dp_min[node];
		ans_max[node] = dp_max[node];

	}else{

		if(nodes[node].op == '@')return; //葉

		/*■まずはpre_min,pre_maxを求める■*/

		if(nodes[pre].op == '+'){

			pre_min[node] = (ans_min[pre]-dp_min[node]);
			pre_max[node] = (ans_max[pre]-dp_max[node]);

		}else{ //nodes[pre].op == '-'

			vector<int> vec;

			if(pre == 0){ //■preがroot

				//■自分以外の2つの子を求める
				for(int i = 0; i < children[pre].size(); i++){

					int child = children[pre][i];
					if(child == node)continue;

					vec.push_back(child);
				}

				int a = vec[0];
				int b = vec[1];

				pre_min[node] = min(dp_min[a]-dp_max[b],dp_min[b]-dp_max[a]);
				pre_max[node] = max(dp_max[a]-dp_min[b],dp_max[b]-dp_min[a]);

			}else{  //■preがrootでない

				int tmp_min = pre_min[pre];
				int tmp_max = pre_max[pre];

				int a;
				for(int i = 0; i < children[pre].size(); i++){

					int child = children[pre][i];
					if(child != node){

						a = child;
						break;
					}
				}

				pre_min[node] = min(dp_min[a]-tmp_max,tmp_min-dp_max[a]);
				pre_max[node] = max(dp_max[a]-tmp_min,tmp_max-dp_min[a]);
			}
		}

		/*■ans_min,ans_maxを計算する■*/

		if(nodes[node].op == '+'){

			ans_max[node] = dp_max[node]+pre_max[node];
			ans_min[node] = dp_min[node]+pre_min[node];

		}else{ //nodes[node].op == '-'

			int a = children[node][0];
			int b = children[node][1];

			ans_max[node] = dp_max[a]-(dp_min[b]+pre_min[node]);
			ans_max[node] = max(ans_max[node],dp_max[b]-(dp_min[a]+pre_min[node]));
			ans_max[node] = max(ans_max[node],pre_max[node]-(dp_min[a]+dp_min[b]));


			ans_min[node] = dp_min[a]-(dp_max[b]+pre_max[node]);
			ans_min[node] = min(ans_min[node],dp_min[b]-(dp_max[a]+pre_max[node]));
			ans_min[node] = min(ans_min[node],pre_min[node]-(dp_max[a]+dp_max[b]));
		}
	}

	for(int i = 0; i < children[node].size(); i++){

		int child = children[node][i];
		dfs2(child,node);
	}
}

void func(){

	for(int i = 0; i < MAX_DEPTH; i++){

		V[i].clear();
	}
	for(int i = 0; i < SIZE; i++){

		children[i].clear();
	}

	int len;
	for(len = 0; line[len] != '\0'; len++);

	int dep = 0;

	//各深さにおける演算子の位置を前計算
	for(int i = 0; i < len; i++){
		if(line[i] == '('){

			dep++;

		}else if(line[i] == ')'){

			dep--;

		}else if(line[i] == '-' || line[i] == '+'){

			V[dep].push_back(i);
		}
	}

	num_node = 0;

	//初期状態の木構造取得
	calc_E(0,len-1,0);

	for(int i = 0; i <= num_node; i++){

		dp_min[i] = BIG_NUM;
		dp_max[i] = -BIG_NUM;

		ans_min[i] = BIG_NUM;
		ans_max[i] = -BIG_NUM;
	}

	dfs(0);
	dfs2(0,-1);

	int ans = -BIG_NUM;
	for(int i = 0; i <= num_node; i++){
		if(nodes[i].op == '@')continue;
		ans = max(ans,ans_max[i]);
	}

	printf("%d\n",ans);
}

int main(){

	while(true){

		scanf("%s",line);
		if(line[0] == '-' && line[1] == '1' && line[2] == '\0')break;

		func();
	}

	return 0;
}
