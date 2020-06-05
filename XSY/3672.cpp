#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=2e5+5;
int n,q,v1[N];
lint v2[N],tag[N],apd[N];

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

namespace B{
	lint tr[N];
	inline void add(int x,const int v){
		for(; x<=n; x+=x&-x) tr[x]+=v;
	}
	inline lint ask(int x){
		lint ans=0;
		for(; x; x-=x&-x) ans+=tr[x];
		return ans;
	}
}

namespace G{
	int cnt,fir[N],fa[N],sz[N],son[N],dep[N],dfn[N],top[N];
	struct edge{
		int to,nx;
	}eg[N];

	inline void add(const int a,const int b){
		fa[b]=a;
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs_dfn(const int x){
		static int cnd;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		dep[x]=dep[fa[x]]+1;
		if(x<=n) dfn[x]=++cnd;
		if(son[x]) dfs_dfn(son[x]);
		for(int i=fir[x]; i; i=eg[i].nx){
			if(eg[i].to!=son[x]) dfs_dfn(eg[i].to);
		}
	}

	void build(){
		static int stk[N];
		int top=0;
		stk[++top]=n+1;
		for(int i=n; i; --i){
			while(v1[stk[top]]<=v1[i]) --top;
			add(stk[top],i);
			stk[++top]=i;
		}
		for(int i=1; i<=n; ++i){
			if(++sz[i]>sz[son[fa[i]]]) son[fa[i]]=i;
			sz[fa[i]]+=sz[i];
		}
		dfs_dfn(n+1);
		for(int i=1; i<=n; ++i){
			B::add(dfn[i],v2[i]);
		}
	}

	lint getsum(int x,int f){
		assert(f!=n+1);
		if(top[f]==f&&apd[f]!=tag[fa[f]]){
			lint dlt=tag[fa[f]]-apd[f];
			B::add(dfn[f],dlt);
			v2[f]+=dlt,apd[f]+=dlt;
		}
		return B::ask(dfn[x])-B::ask(dfn[f]-1);
	}

	lint solve(int a,int b){
		int x=a,y=b;
		lint ans=0;
		while(top[x]!=top[y]){
			if(dep[top[x]]>dep[top[y]]) ans+=getsum(x,top[x]),x=fa[top[x]];
			else ans+=getsum(y,top[y]),y=fa[top[y]];
		}
		if(x>n||y>n) return 1ll<<63;
		if(dep[x]>dep[y]) ans+=getsum(x,y),x=y;
		else ans+=getsum(y,x),y=x;
		if(x==a||x==b){
			if((x=fa[x])==n+1) return 1ll<<63;
			ans+=getsum(x,x);
		}
		return ans;
	}
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		v1[i]=nxi();
	}
	v1[n+1]=1e8;
	for(int i=1; i<=n; ++i){
		v2[i]=nxi();
	}
	G::build();
	for(int i=1; i<=q; ++i){
		int op=nxi(),a=nxi(),b=nxi();
		if(op==1){
			int c=G::son[a];
			v2[a]+=b;
			B::add(G::dfn[a],b);
			if(c){
				v2[c]+=b;
				B::add(G::dfn[c],b);
			}
			tag[a]+=b;
		}
		else{
			lint res=G::solve(a,b);
			if(res==1ll<<63) puts("?");
			else printf("%lld\n",res);
		}
	}
	return 0;
}
