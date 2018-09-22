#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1e5+2;
int n,m,ans,cnf,fa[N],fir[N],bel[N],dgr[N];
bool vis[N];
struct edge{
	int to,nx;
}eg[N<<2];

inline void apn(int &x,const int y){
	if(x>y) x=y;
}

inline void add(const int a,const int b){
	static int cnt=0;
	eg[++cnt]=(edge){b,fir[a]};
	fir[a]=cnt;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

void dfs(const int x){
	static int cnd,top,dfn[N],low[N],stk[N];
	static bool inq[N];
	stk[++top]=x;
	inq[x]=1;
	dfn[x]=low[x]=++cnd;
	for(int i=fir[x];i;i=eg[i].nx){
		const int y=eg[i].to;
		if(y==fa[x]) continue;
		if(!dfn[y]){
			fa[y]=x;
			dfs(y);
			apn(low[x],low[y]);
		}else{
			if(inq[y]) apn(low[x],dfn[y]);
		}
	}
	if(low[x]==dfn[x]){
		int j=0;
		++cnf;
		while(j!=x){
			j=stk[top--];
			bel[j]=cnf;
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=m;++i){
		const int x=nxi(),y=nxi();
		add(x,y);
		add(y,x);
	}
	dfs(1);
	ans=cnf;
	for(int x=1;x<=n;++x){
		const int a=bel[x];
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=bel[eg[i].to];
			if(a==y) continue;
			if(!dgr[a]) dgr[a]=y;
			else if(dgr[a]!=y&&!vis[a]){
				vis[a]=1;
				--ans;
				break;
			}
		}
	}
	printf("%d\n",(ans+1)>>1);
	return 0;
}
