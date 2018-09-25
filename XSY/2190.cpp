#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1e5+2;
int n,fir[N],dp[N<<1],len[N<<1];
int sz[N],fa[N],son[N],top[N],dep[N];
struct edge{
	int to,nx;
}eg[N<<1];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

template <class T> inline void xswp(T &x,T &y){
	if(x<y) std::swap(x,y);
}

inline void add(const int x,const int y){
	static int cnt=1;
	eg[++cnt]=(edge){y,fir[x]};
	fir[x]=cnt;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

void dfs1(const int x){
	sz[x]=1;
	for(int i=fir[x];i;i=eg[i].nx){
		const int y=eg[i].to;
		if(!sz[y]){
			fa[y]=x;
			dep[y]=dep[x]+1;
			dfs1(y);
			if(sz[y]>sz[son[x]]) son[x]=y;
			sz[x]+=sz[y];
		}
	}
}

void dfs2(const int x){
	top[x]=son[fa[x]]==x?top[fa[x]]:x;
	for(int i=fir[x];i;i=eg[i].nx){
		const int y=eg[i].to;
		if(!top[y]) dfs2(y);
	}
}

//e: point to x
void dfs_down(const int x,const int e){
	for(int i=fir[x];i;i=eg[i].nx){
		if((i^1)==e) continue;
		const int y=eg[i].to;
		dep[y]=dep[x]+1;
		dfs_down(y,i);
		apx(dp[e],dp[i]);
		apx(dp[e],len[e]+len[i]+1);
		apx(len[e],len[i]+1);
	}
}

void dfs_up(const int x,const int e){
	int len1=0,len2=0,dp1=0,dp2=0;
	for(int i=fir[x];i;i=eg[i].nx){
		int tp=len[i]+1;
		xswp(len1,tp);
		xswp(len2,tp);
		tp=dp[i];
		xswp(dp1,tp);
		xswp(dp2,tp);
	}
	for(int i=fir[x];i;i=eg[i].nx){
		const int p=i^1;
		if(p==e) continue;
		len[p]=len[i]==len1?len2:len1;
		dp[p]=dp[i]==dp1?dp2:dp1;
	}
}

inline int get_lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
		else y=fa[top[y]];
	}
	return dep[x]<dep[y]?x:y;
}

int main(){
	n=nxi();
	for(int i=1;i<n;++i){
		const int x=nxi(),y=nxi();
		add(x,y);
		add(y,x);
	}
	dfs1(1);
	dfs2(1);
	dfs_down(1,0);
	dfs_up(1,0);
	return 0;
}
