#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=3e5+5;
const int mod=998244353;
int n,m,q,tot;

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

template <size_t T>
struct _G{
	int cnt,fir[T];
	struct edge{
		int to,nx;
	}eg[T<<1];
	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,fir[b]};
		fir[b]=cnt;
	}
};

namespace B{
	int tr[N<<1];
	inline void add(int x,const int v){
		for(; x<=tot; x+=x&-x) tr[x]=(tr[x]+v)%mod;
	}
	inline void add_seg(const int x,const int y,const int v){
		add(x,v),add(y+1,-v);
	}
	inline int ask(int x){
		int ans=0;
		for(; x; x-=x&-x) ans=(ans+tr[x])%mod;
		return ans;
	}
}

struct RST:_G<N<<1>{
	const static int N=::N<<1;
	int sz[N],fa[N],dep[N],dfn[N],son[N],top[N];
	int stag[N],rtag[N];//square,round
	void dfs_son(const int x){
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(sz[y]) continue;
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
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		if(!son[x]) return;
		dfs_top(son[x]);
		for(int i=fir[x]; i; i=eg[i].nx){
			if(!dfn[eg[i].to]) dfs_top(eg[i].to);
		}
	}
	void upd_to_f(const int x){
		int f=fa[x],dlt=(B::ask(dfn[x])-stag[x])%mod;
		assert(x>=n&&fa[x]<=n);
		stag[x]=(stag[x]+dlt)%mod;
		rtag[f]=(rtag[f]+dlt)%mod;
	}
	void setv(int x,int y,const int v){
		rtag[x]=(rtag[x]+v)%mod;
		rtag[y]=(rtag[y]+v)%mod;
		while(top[x]!=top[y]){
			if(dep[top[x]]<dep[top[y]]) std::swap(x,y);
			int f=top[x];
			B::add_seg(dfn[f],dfn[x],v);
			if(f>n) upd_to_f(f);
			x=fa[f];
		}
		if(dep[x]<dep[y]) std::swap(x,y);
		B::add_seg(dfn[y],dfn[x],v);
		if(top[y]==y&&y>n) upd_to_f(y);
	}
	int qry(const int x){
		int ans=(rtag[x]-B::ask(dfn[x]))%mod;
		if(son[x]) ans=(ans+B::ask(dfn[son[x]]))%mod;
		if(fa[x]) ans=(ans+B::ask(dfn[fa[x]]))%mod;
		return (ans+mod)%mod;
	}
}T;

struct org_G:_G<N<<1>{
	int dfn[N],low[N];
	bool vis[N];
	void tarjan(const int x){
		static int cnd,top,stk[N];
		stk[++top]=x;
		low[x]=dfn[x]=++cnd;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!dfn[y]){ 
				tarjan(y);
				if(low[y]>=dfn[x]){
					++tot;
					while(stk[top]!=x){
						T.add(tot+n,stk[top--]);
					}
					T.add(tot+n,x);
				}
				apn(low[x],low[y]);
			}
			else apn(low[x],dfn[y]);
		}
	}
}G;

int main(){
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1; i<=m; ++i)
		G.add(nxi(),nxi());
	G.tarjan(1);
	tot+=n;
	T.dfs_son(1);
	T.dfs_top(1);
	for(int i=1; i<=q; ++i){
		const int op=nxi();
		if(op==0){
			int x=nxi(),y=nxi(),v=nxi();
			T.setv(x,y,v);
		}
		else printf("%d\n",T.qry(nxi()));
	}
	return 0;
}
