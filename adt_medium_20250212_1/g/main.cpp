#include<iostream>
#include<set>

using namespace std;

int H,W;
set<int>R[4<<17],C[4<<17];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int Q;
	cin>>H>>W>>Q;
	for(int i=0;i<H;i++)for(int j=0;j<W;j++)
	{
		R[i].insert(j);
		C[j].insert(i);
	}
	auto bomb=[](int r,int c){
		if(r==-1||c==-1)return;
		R[r].erase(c);
		C[c].erase(r);
	};
	for(;Q--;)
	{
		int r,c;cin>>r>>c;r--,c--;
		auto it=R[r].lower_bound(c);
		if(it!=R[r].end()&&*it==c)
		{
			bomb(r,c);
			continue;
		}
		int c1=-1,c2=-1;
		if(it!=R[r].end())c2=*it;
		if(it!=R[r].begin())c1=*prev(it);
		int r1=-1,r2=-1;
		auto jt=C[c].lower_bound(r);
		if(jt!=C[c].end())r2=*jt;
		if(jt!=C[c].begin())r1=*prev(jt);
		bomb(r,c1);
		bomb(r,c2);
		bomb(r1,c);
		bomb(r2,c);
	}
	int ans=0;
	for(int i=0;i<H;i++)ans+=R[i].size();
	cout<<ans<<endl;
}
