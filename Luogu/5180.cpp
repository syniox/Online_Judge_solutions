#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cassert>
const int N=2e5+5;
int n,m;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

namespace U{
	int fa[N],npt[N];//min point(based on dfn)
}

namespace G{
	int cnt,fa[N],sz[N],fir[N],dfn[N],idx[N],idom[N],sdom[N];
	std::vector <int> g[N],inv_g[N],qry[N];
}

namespace U{
	inline void init(){
		for(int i=1; i<=n; ++i) npt[i]=i;
	}
	int find_rt(const int x){
		if(!fa[x]) return x;
		assert(fa[x]!=x);
		int res=find_rt(fa[x]);
		if(G::sdom[npt[x]]>G::sdom[npt[fa[x]]]){
			npt[x]=npt[fa[x]];
		}
		return fa[x]=res;
	}
	inline int find_mn(const int x){
		return find_rt(x),npt[x];
	}
}

namespace G{
	inline void dfs_dfn(const int x){
		static int cnd;
		dfn[x]=++cnd;
		idx[cnd]=x;
		for(std::vector <int> ::iterator it=g[x].begin(); it!=g[x].end(); ++it){
			if(!dfn[*it]) fa[*it]=x,dfs_dfn(*it);
		}
	}

	inline void get_dom(){
		U::init();
		for(int i=1; i<=n; ++i) sdom[i]=i;
		for(int i=n; i; --i){
			std::vector <int> ::iterator it;
			const int x=idx[i];
			for(it=inv_g[x].begin(); it!=inv_g[x].end(); ++it){
				apn(sdom[i],sdom[U::find_mn(dfn[*it])]);
			}
			qry[sdom[i]].push_back(i);
			for(it=qry[i].begin(); it!=qry[i].end(); ++it){//base on dfn
				idom[*it]=U::find_mn(*it);//not real idom
			}
			for(it=g[x].begin(); it!=g[x].end(); ++it){
				if(fa[*it]==x) U::fa[dfn[*it]]=i;
			}
		}
		for(int i=2; i<=n; ++i){
			if(sdom[idom[i]]==sdom[i]) idom[i]=sdom[i];
			else idom[i]=idom[idom[i]];
		}
		for(int i=n; i>1; --i){
			sz[idx[idom[i]]]+=++sz[idx[i]];
		}
		++sz[1];
	}
}

int main(){
	n=nxi(),m=nxi();
	U::init();
	for(int i=1; i<=m; ++i){
		const int a=nxi(),b=nxi();
		G::g[a].push_back(b);
		G::inv_g[b].push_back(a);
	}
	G::dfs_dfn(1);
	G::get_dom();
	for(int i=1; i<=n; ++i){
		printf("%d ",G::sz[i]);
	}
	puts("");
	return 0;
}
