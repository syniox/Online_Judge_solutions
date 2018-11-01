#include <iostream>
#include <cstdio>
#include <cstring>
const int N=2e5+5;
int n,m,q,rt,col[N],fir[N],ans[N],bel[N];
bool vis[N];
struct edge{
	int to,wi,nx;
}eg[N*3];

inline void add_edge(const int a,const int b,const int v){
	static int cnt;
	eg[++cnt]=(edge){b,v,fir[a]};
	fir[a]=cnt;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

bool dfs(const int x){
	bel[x]=rt;
	vis[x]=1;
	for(int i=fir[x];i;i=eg[i].nx){
		const int y=eg[i].to;
		if(!vis[y]){
			col[y]=col[x]^eg[i].wi;
			if(!dfs(y)) return 0;
		}
		else if((col[x]^col[y])!=eg[i].wi) return 0;
	}
	return 1;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1;i<=m;++i){
		const int a=nxi(),b=nxi(),v=nxi();
		add_edge(a,b,v);
		add_edge(b,a,v);
	}
	for(int i=1;i<=n;++i){
		if(!vis[i]){
			rt=i;
			if(!dfs(i)){
				puts("-1");
				return 0;
			}
		}
	}
	for(int i=1;i<=n;++i){
		if(bel[i]==rt) col[i]^=(q-1);
		printf("%d ",col[i]);
	}
	puts("");
	return 0;
}
