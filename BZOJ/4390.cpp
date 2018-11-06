#include <iostream>
#include <cstdio>
#include <cstring>
const int N=1e5+2;
int n,m,cf[N];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline char get_c(){
	static char *h,*t,buf[200000];
	if(h==t){
		t=(h=buf)+fread(buf,1,200000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=get_c())>'9'||c<'0');
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,fa[N],sz[N],son[N],top[N],fir[N],dep[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs1(const int x){
		sz[x]=1;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!sz[y]){
				dep[y]=dep[x]+1;
				fa[y]=x;
				dfs1(y);
				if(sz[y]>sz[son[x]]) son[x]=y;
				sz[x]+=sz[y];
			}
		}
	}

	void dfs2(const int x){
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		if(son[x]) dfs2(son[x]);
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!top[y]) dfs2(y);
		}
	}

	inline int lca(int x,int y){
		while(top[x]!=top[y]){
			if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
			else y=fa[top[y]];
		}
		return dep[x]<dep[y]?x:y;
	}

	int dfs3(const int x){
		int ans=0;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa[x]){
				apx(ans,dfs3(y));
				cf[x]+=cf[y];
			}
		}
		return std::max(ans,cf[x]);
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<n;++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	G::dfs1(1);
	G::dfs2(1);
	while(m--){
		const int x=nxi(),y=nxi(),z=G::lca(x,y);
		++cf[x],++cf[y];
		--cf[z],--cf[G::fa[z]];
	}
	printf("%d\n",G::dfs3(1));
	return 0;
}
