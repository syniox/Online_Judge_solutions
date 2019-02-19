#include <iostream>
#include <cstdio>
#include <cstring>
const int N=5e5+5;
int n,m;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,fir[N],fa[N],dep[N],top[N],sz[N],son[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	inline void dfs1(const int x){
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa[x]){
				fa[y]=x;
				dep[y]=dep[x]+1;
				dfs1(y);
				if(sz[y]>sz[son[x]]) son[x]=y;
				sz[x]+=sz[y];
			}
		}
	}

	inline void dfs2(const int x){
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!top[y]) dfs2(y);
		}
	}

	inline int get_lca(int x,int y){
		while(top[x]!=top[y]){
			if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
			else y=fa[top[y]];
		}
		return dep[x]<dep[y]?x:y;
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	G::dfs1(1);
	G::dfs2(1);
	for(int i=1; i<=m; ++i){
		using G::dep;
		const int a=nxi(),b=nxi(),c=nxi();
		int lca1=G::get_lca(a,b);
		int lca2=G::get_lca(b,c);
		int lca3=G::get_lca(a,c);
		printf("%d %d\n",lca1^lca2^lca3,dep[a]+dep[b]+dep[c]-dep[lca1]-dep[lca2]+dep[lca3]);
	}
	return 0;
}
