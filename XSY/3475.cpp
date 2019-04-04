#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=2e5+5;
int n,m,f1[N],f2[N];
bool v1[N],v2[N],ans[N<<1];

template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

inline int nxi(){
	int x=0;
	char c;
	while(((c=getchar())>'9'||c<'0')&&c!='-');
	const bool f=(c=='-')&&(c=getchar());
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return f?-x:x;
}

namespace G{
	int cnt,fir[N<<1],tick,tag[N<<1];
	int cnd,c_scc,dfn[N<<1],low[N<<1],bel[N<<1];
	struct edge{
		int to,nx;
	}eg[N<<2];

	void clear(){
		cnt=cnd=c_scc=0;
		++tick;
	}

	inline void upd(const int x){
		if(tag[x]!=tick){
			tag[x]=tick;
			fir[x]=dfn[x]=bel[x]=0;
		}
	}

	inline void add(const int a,const int b){
		upd(a),upd(b);
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void tarjan(const int x){
		static int stk[N],top;
		stk[++top]=x;
		low[x]=dfn[x]=++cnd;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!dfn[y]){
				tarjan(y);
				apn(low[x],low[y]);
			}
			else{
				if(!bel[y]) apn(low[x],dfn[y]);
			}
		}
		if(low[x]<dfn[x]) return;
		++c_scc;
		for(int j=stk[top--]; ; j=stk[top--]){
			bel[j]=c_scc;
			if(j==x) break;
		}
	}
}

namespace T{
	int cnt,fa[N<<1],fir[N<<1];
	int sz[N<<1],dep[N<<1],son[N<<1],idx[N<<1],dfn[N<<1],top[N<<1],bot[N<<1];
	int list[N],list_sz;
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs_son(const int x){
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			fa[y]=x;
			dep[y]=dep[x]+1;
			dfs_son(y);
			if(sz[y]>sz[son[x]]) son[x]=y;
			sz[x]+=sz[y];
		}
	}

	void dfs_top(const int x){
		static int cnd;
		dfn[x]=++cnd;
		idx[cnd]=x;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		bot[top[x]]=x;
		if(son[x]) dfs_top(son[x]);
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!top[y]) dfs_top(y);
		}
	}

	void dfs_edge(const int x){
		if(x<=m){
			G::add(f1[x]+v1[x]*n,f2[x]+(v2[x]^1)*n);
			G::add(f2[x]+v2[x]*n,f1[x]+(v1[x]^1)*n);
			list[++list_sz]=f1[x];
			list[++list_sz]=f2[x];
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			dfs_edge(eg[i].to);
		}
	}

	bool jdg(const int x){
		G::clear();
		list_sz=0;
		dfs_edge(x);
		for(int i=1; i<=list_sz; ++i){
			if(!G::dfn[list[i]]) G::tarjan(list[i]);
		}
		for(int i=1; i<=list_sz; ++i){
			if(G::bel[list[i]]==G::bel[list[i]+n]) return 0;
		}
		return 1;
	}

	void solve(const int x){
		const int y=bot[x];
		int l=0,r=dep[y]-dep[x]+1,mid;
		while(l!=r){
			mid=(l+r)>>1;
			if(jdg(idx[dfn[x]+mid])) r=mid;
			else l=mid+1;
		}
		if(l<=dep[y]-dep[x]){
			ans[idx[dfn[x]+l]]=1;
		}
	}

	void dfs_ans(const int x){
		if(ans[fa[x]]==1) ans[x]=1;
		else if(top[x]==x) solve(x);
		for(int i=fir[x]; i; i=eg[i].nx){
			dfs_ans(eg[i].to);
		}
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=m; ++i){
		int p=nxi(),q=nxi();
		if(p<0) v1[i]=1,p=-p;
		if(q<0) v2[i]=1,q=-q;
		f1[i]=p,f2[i]=q;
	}
	for(int i=m+1; i<m<<1; ++i){
		T::add(i,nxi());
		T::add(i,nxi());
	}
	T::dfs_son((m<<1)-1);
	T::dfs_top((m<<1)-1);
	T::dfs_ans((m<<1)-1);
	for(int i=m+1; i<m<<1; ++i){
		putchar('0'+ans[i]);
	}
	puts("");
	return 0;
}
