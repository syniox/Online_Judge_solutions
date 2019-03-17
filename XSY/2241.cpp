#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cassert>
const int N=1005;
int n,m;
class _Pair{
	public:
		int x,y;
		friend inline bool operator < (const _Pair &a,const _Pair &b){
			return a.x==b.x?a.y<b.y:a.x<b.x;
		}
};
std::vector <_Pair> pbuk;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace U{
	int fa[N],npt[N];//original order(not dfn)
}

namespace L{
	int nxt[N],end[N];
}

namespace G{
	int sz[N],fa[N],idx[N],dfn[N],sdom[N],idom[N];
	std::vector <int> g[N],inv_g[N],qry[N];
}

namespace L{
	inline void init(){
		for(int i=1; i<=n; ++i) end[i]=i;
	}
	inline void link(const int a,const int b){
		assert(!nxt[end[a]]);
		nxt[end[a]]=b;
		end[a]=end[b];
	}
}

namespace U{
	using G::sdom;using G::dfn;
	inline void init(){
		for(int i=1; i<=n; ++i) npt[i]=i;
	}
	inline int find_rt(const int x){
		if(!fa[x]) return x;
		int res=find_rt(fa[x]);
		if(dfn[sdom[npt[fa[x]]]]<dfn[sdom[npt[x]]]){
			npt[x]=npt[fa[x]];
		}
		return res;
	}
	inline int find_mn(const int x){
		return find_rt(x),npt[x];
	}
}

namespace G{
	inline void add(const int a,const int b){
		g[a].push_back(b);
		inv_g[b].push_back(a);
	}

	inline void dfs_dfn(const int x){
		static int cnd;
		dfn[x]=++cnd,idx[cnd]=x;
		for(std::vector <int> ::iterator it=g[x].begin(); it!=g[x].end(); ++it){
			if(!dfn[*it]) fa[*it]=x,dfs_dfn(*it);
		}
	}

	inline void oput_nodfn(){
		int res=0;
		for(int i=1; i<=n; ++i){
			if(!dfn[i]) ++res;
		}
		printf("%d\n",res);
		for(int i=1; i<=n; ++i){
			if(!dfn[i]) printf("%d\n",i-1);
		}
	}

	inline void get_dom(){
		for(int i=1; i<=n; ++i) sdom[i]=i;
		for(int i=n; i; --i){
			if(!idx[i]) continue;
			const int x=idx[i];
			std::vector <int> ::iterator it;
			for(it=inv_g[x].begin(); it!=inv_g[x].end(); ++it){
				if(!dfn[*it]) continue;
				int res=U::find_mn(*it);
				if(dfn[sdom[x]]>dfn[sdom[res]]) sdom[x]=sdom[res]; 
			}
			qry[sdom[x]].push_back(x);
			for(it=qry[x].begin(); it!=qry[x].end(); ++it){
				idom[*it]=U::find_mn(*it);//not real idom
			}
			for(it=g[x].begin(); it!=g[x].end(); ++it){
				if(fa[*it]==x) U::fa[*it]=x;
			}
		}
		for(int i=1; idx[i]&&i<=n; ++i){
			if(sdom[idom[idx[i]]]==sdom[idx[i]]) idom[idx[i]]=sdom[idx[i]];
			else idom[idx[i]]=idom[idom[idx[i]]];
		}
	}

	inline void get_lnk(){
		static int buk[N];
		int ans=0;
		for(int i=n; i>1; --i){
			if(idom[idx[i]]==0) continue;
			++sz[idx[i]];
			if(idom[idx[i]]==1){
				ans+=sz[idx[i]]*(sz[idx[i]]-1)>>1;
			}
			else{
				sz[idom[idx[i]]]+=sz[idx[i]];
				L::link(idom[idx[i]],idx[i]);
			}
		}
		printf("%d\n",ans);
		if(ans>10000) return;
		for(int i=2; i<=n; ++i){
			if(idom[i]!=1) continue;
			int pt=0;
			for(int j=i; j; j=L::nxt[j]) buk[pt++]=j;
			for(int j=0; j<pt; ++j){
				for(int k=j+1; k<pt; ++k){
					int x=buk[j],y=buk[k];
					if(x>y) std::swap(x,y);
					pbuk.push_back((_Pair){x-1,y-1});
				}
			}
		}
		std::sort(pbuk.begin(),pbuk.end());
		for(std::vector <_Pair> ::iterator it=pbuk.begin(); it!=pbuk.end(); ++it){
			printf("%d %d\n",it->x,it->y);
		}
	}
}

int main(){
	n=nxi()+1,m=nxi();
	U::init();
	L::init();
	for(int i=2; i<=m+1; ++i){
		for(int j=nxi(); j; --j) G::add(nxi()+1,i);
	}
	for(int i=m+2; i<=n; ++i){
		G::add(1,i);
	}
	G::dfs_dfn(1);
	G::oput_nodfn();
	G::get_dom();
	G::get_lnk();
	return 0;
}
