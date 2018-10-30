#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
const int N=5e4+5;
int n,m,q,ans,dp[N],fir[N],link[N];
bool imp[N],vis[N];
std::vector <int> route[N];
struct edge{
	int to,nx;
}eg[N<<1];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())<'0');
	while(x=x*10-48+c,(c=getchar())>='0');
	return x;
}

inline void add_edge(const int a,const int b){
	static int cnt;
	eg[++cnt]=(edge){b,fir[a]};
	fir[a]=cnt;
}

void dfs(const int x,const int fa){
	dp[x]=imp[x]?x:0;
	vis[x]=1;
	if(dp[x]) route[x].push_back(x);
	for(int i=fir[x];i;i=eg[i].nx){
		const int y=eg[i].to;
		if(y==fa||vis[y]) continue;
		dfs(y,x);
		if(!dp[y]) continue;
		if(!dp[x]){
			dp[x]=dp[y];
			route[dp[x]].push_back(x);
		}
		else{
			link[dp[x]]=dp[y];
			link[dp[y]]=dp[x];
			++ans;
			dp[x]=0;
		}
	}
}

inline void oput(const int x){
	const int y=link[x];
	const int l1=route[x].size(),l2=route[y].size();
	printf("%d ",l1+l2-1);
	for(int i=0;i<l1;++i){
		printf("%d ",route[x][i]);
	}
	for(int i=l2-1;i>=0;--i){
		printf("%d ",route[y][i]);
	}
	puts("");
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1;i<=m;++i){
		const int a=nxi(),b=nxi();
		add_edge(a,b);
		add_edge(b,a);
	}
	for(int i=1;i<=q;++i){
		imp[nxi()]=1;
	}
	for(int i=1;i<=n;++i){
		if(!vis[i]) dfs(i,0);
	}
	printf("%d\n",ans);
	for(int i=1;i<=n;++i){
		if(link[i]&&i<link[i]) oput(i);
	}
	return 0;
}
