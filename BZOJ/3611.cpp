#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=1e6+5;
int n,q,cnt,fi[N],fir[N],dfn[N],req[N],stk[N];
int sz[N],dp[N],dis[N],st[N][2],lt[N][2],dep[N],fa[N][21];
bool vis[N];
struct edge{
	int to,nx;
}eg[N],gg[N];

inline bool cmp(int x,int y){
	return dfn[x]<dfn[y];
}

inline void add(edge* eg,int* fir,int a,int b){
	eg[++cnt]=(edge){b,fir[a]};
	fir[a]=cnt;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<'9');
	return x;
}

void init(int x){
	for(int i=1;fa[x][i-1];++i){
		fa[x][i]=fa[fa[x][i-1]][i-1];
	}
	dfn[x]=++cnt;
	for(int i=fi[x];i;i=gg[i].nx){
		int y=gg[i].to;
		if(!dfn[y]){
			fa[y][0]=x;
			init(y);
		}
	}
}

int lca(int x,int y){
	if(dep[x]>dep[y]) swap(x,y);
	int tp=dep[y]-dep[x];
	for(int i=0;i<21;++i){
		if((1<<i)&tp) y=fa[y][i];
	}
	if(x==y) return x;
	for(int i=20;~i;--i){
		if(fa[x][i]!=fa[y][i]){
			x=fa[x][i];
			y=fa[y][i];
		}
	}
	return fa[x][0];
}

void dfs(int x){
	vis[x]=1;
	int tp=0;
	for(int i=fir[x];i;i=eg[i].nx){
		int y=eg[i].to;
		if(!vis[y]){
			dfs(y);
			dis[x]+=dis[y]+sz[y];
			tp+=sz[y];
		}
	}
	for(int i=fir[x];i;i=eg[i].nx){
		int y=eg[i].to;
		if(!vis[y]){
			dis[x]+=dis[y]+sz[y];
			dp[x]+=dp[y]+dis[y]*(tp-sz[y]);
			sz[y]=dp[y]=dis[y]=0;
		}
	}
	sz[x]+=tp;
	vis[x]=0;
}

int main(){
	n=nxi();
	for(int a,b,i=1;i<n;++i){
		a=nxi(),b=nxi();
		add(gg,fi,a,b);
	}
	cnt=0;
	init(1);
	cnt=0;
	for(int k;q--;){
		k=nxi();
		for(int i=1;i<=k;++i){
			++sz[req[i]=nxi()];
		}
		sort(req+1,req+k+1,cmp);
		int top=0;
		for(int i=1;i<=k;++i){
			if(!top) stk[++top]=req[i];
			int f(0),p=lca(stk[top],req[i]);
			while(dep[stk[top]]>dep[p]) --top,f=1;
			if(top&&dep[stk[top]]==dep[p]){
				add(eg,fir,stk[top],req[i]);
			}
			else{
				if(top) add(eg,fir,stk[top],p);
				if(f) add(eg,fir,p,stk[top+1]);
				add(eg,fir,p,req[i]);
			}
			stk[++top]=req[i];
		}
		dfs(stk[1]);
		printf("%d\n",dp[stk[1]]);
		dp[stk[1]]=sz[stk[1]]=dis[stk[1]]=0;
	}
	return 0;
}
