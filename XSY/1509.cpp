#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
const int N=1e5+2;
int n,m;
double dp[N],prc[N],cost[N];
struct edge{
	int t;
	double w,p;
	bool operator < (const edge &b) const {
		return b.p*(w+p*dp[t])<p*(b.w+b.p*dp[b.t]);
	}
};
std::vector <edge> vt[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void solve(const int x){
	std::sort(vt[x].begin(),vt[x].end());
	int i,sz=vt[x].size();
	for(i=0;i<sz;++i){
		if(vt[x][i].t==x+1&&vt[x][i].w==cost[x+1]&&vt[x][i].p==1) break;
	}
	for(;i>=0;--i){
		dp[x]=vt[x][i].w+vt[x][i].p*dp[vt[x][i].t]+(1-vt[x][i].p)*dp[x];
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("1509.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=2;i<=n;++i){
		scanf("%lf",cost+i);
		prc[i]=prc[i-1]+cost[i];
		vt[i-1].push_back((edge){i,cost[i],1});
	}
	for(int i=1;i<=m;++i){
		edge tp;
		const int s=nxi();
		tp.t=nxi();
		scanf("%lf",&tp.p);
		tp.w=nxi();
		vt[s].push_back(tp);
	}
	for(int i=n-1;i;--i){
		solve(i);
	}
	printf("%.2lf\n",dp[1]);
	return 0;
}
