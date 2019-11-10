#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=2e5+5;
const int mod=1e9+7;
int n;

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

namespace U{
	int fa[N<<1];
	int find_rt(const int x){
		return fa[x]?fa[x]=find_rt(fa[x]):x;
	}
}

namespace G{
	int cnt,fir[N<<1],dfn[N<<1],fa[N<<1],dep[N<<1],sz[N<<1],son[N<<1],top[N<<1];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		fa[b]=a;
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	bool cmp_dfn(const int a,const int b){
		return dfn[a]<dfn[b];
	}

	void get_son(){
		for(int i=1; i<n*2; ++i){
			sz[fa[i]]+=++sz[i];
			if(sz[son[fa[i]]]<sz[i]) son[fa[i]]=i;
		}
		son[0]=0;
	}

	void dfs_dfn(const int x){
		static int cnd;
		dfn[x]=++cnd;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		dep[x]=dep[fa[x]]+1;
		for(int i=fir[x]; i; i=eg[i].nx){
			dfs_dfn(eg[i].to);
		}
	}

	int get_lca(int x,int y){
		while(top[x]!=top[y]){
			if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
			else y=fa[top[y]];
		}
		return dep[x]<dep[y]?x:y;
	}
}

int main(){
	n=nxi();
	for(int i=1; i<n; ++i){
		const int a=U::find_rt(nxi()),b=U::find_rt(nxi());
		G::add(n+i,a);
		G::add(n+i,b);
		U::fa[a]=n+i,U::fa[b]=n+i;
	}
	G::get_son();
	G::dfs_dfn(n*2-1);
	for(int q=nxi(); q; --q){
		static int buk[N],lim[N];
		int k=nxi();
		for(int i=1; i<=k; ++i){
			buk[i]=nxi();
		}
		std::sort(buk+1,buk+k+1,G::cmp_dfn);
		lim[1]=n;
		for(int i=2; i<=k; ++i){
			lim[i]=n;
			int v=G::get_lca(buk[i-1],buk[i])-n;
			apn(lim[i],v);
			apn(lim[i-1],v);
		}
		int ans=1;
		for(int i=1; i<=k; ++i){
			ans=(lint)ans*lim[i]%mod;
		}
		printf("%d\n",ans);
	}
	return 0;
}
