#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef const int cint;
typedef long long lint;
cint N=1e5+5;
int n,m;
lint val[N];
bool ol;

namespace utils{
#define eprintf(fmt,...) fprintf(stderr,fmt,##__VA_ARGS__)
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
	int find_rt(cint x){
		return fa[x]?fa[x]=find_rt(fa[x]):x;
	}
}

namespace KST{
	int rt,cnt,fir[N<<1],fa[N<<1],val[N<<1],val_d[N<<1],nsum[N<<1],pfn[N];
	int sz[N<<1],son[N<<1],top[N<<1],dfn[N<<1],idx[N<<1];
	struct edge{
		int to,nx;
	}eg[N<<1];
	inline void add(cint a,cint b){
		fa[b]=a;
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs_top(cint x){
		static int cnd;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		val_d[dfn[x]=++cnd]=val[x];
		idx[cnd]=x;
		nsum[cnd]=nsum[cnd-1]+(x<=n);
		if(x<=n) pfn[x]=nsum[cnd];
		if(son[x]) dfs_top(son[x]);
		for(int i=fir[x]; i; i=eg[i].nx){
			if(!dfn[eg[i].to]) dfs_top(eg[i].to);
		}
	}
	void build(){
		for(int i=1; i<=rt; ++i){
			sz[fa[i]]+=++sz[i];
			if(sz[i]>sz[son[fa[i]]]) son[fa[i]]=i;
		}
		dfs_top(rt);
	}

	void getrng(int x,cint d,int &l,int &r){
		assert(x<=n);
		for(; val[fa[top[x]]]>=d; x=fa[top[x]]);
		l=dfn[top[x]],r=dfn[x];
		while(l!=r){
			int mid=(l+r)>>1;
			if(val_d[mid]<d) l=mid+1;
			else r=mid;
		}
		l=idx[l],r=dfn[l]+sz[l]-1,l=dfn[l];
		l=nsum[l-1]+1,r=nsum[r];
	}
}

namespace G{
	int cnt,sz[N],fir[N],dfn[N];
	struct edge{
		int to,nx;
	}eg[N<<1];
	struct eg2{
		int a,b,v;
		friend bool operator < (const eg2 &a,const eg2 &b){
			return a.v>b.v;
		}
	}e[N];
	inline void add(cint a,cint b,cint v){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,fir[b]};
		fir[b]=cnt;
		e[cnt>>1]=(eg2){a,b,v};
	}
	void kruskal(){
		std::sort(e+1,e+(cnt>>1)+1);
		int tot=n;
		for(int i=1; i<=(cnt>>1); ++i){
			int x=U::find_rt(e[i].a),y=U::find_rt(e[i].b);
			if(x==y) continue;
			++tot;
			KST::add(tot,x);
			KST::add(tot,y);
			U::fa[x]=U::fa[y]=tot;
			KST::val[tot]=e[i].v;
		}
		KST::rt=tot;
	}
	void dfs_dfn(cint x){
		static int cnd;
		dfn[x]=++cnd;
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			cint y=eg[i].to;
			if(!dfn[y]) dfs_dfn(y),sz[x]+=sz[y];
		}
	}
	void getrng(cint x,int &l,int &r){
		l=dfn[x],r=dfn[x]+sz[x]-1;
	}
}

namespace TIT{
	int cnt,x,v,rt[N];
	struct node{
		int lc,rc;
		lint s;
	}tr[N*132];

	inline void upd(const int k){
		tr[k].s=tr[tr[k].lc].s+tr[tr[k].rc].s;
	}
	void add(int &k,cint l,cint r){
		tr[k?k:k=++cnt].s+=v;
		if(l==r) return;
		const int mid=(l+r)>>1;
		if(x<=mid) add(tr[k].lc,l,mid);
		else add(tr[k].rc,mid+1,r);
		upd(k);
	}
	lint ask(cint k,cint l,cint r){
		if(r<=x||!k) return tr[k].s;
		const int mid=(l+r)>>1;
		lint ans=ask(tr[k].lc,l,mid);
		if(x>mid) ans+=ask(tr[k].rc,mid+1,r);
		return ans;
	}

	void ins(int x,cint y,cint v){
		TIT::x=y,TIT::v=v;
		for(; x<=n; x+=x&-x) add(rt[x],1,n); 
	}
	void mdf(cint l0,cint r0,cint l1,cint r1,cint v){
		ins(l0,l1,v);
		if(r1<n) ins(l0,r1+1,-v);
		if(r0<n){
			ins(r0+1,l1,-v);
			if(r1<n) ins(r0+1,r1+1,v);
		}
	}
	lint qry(int x,cint y){
		lint ans=0;
		for(; x; x-=x&-x) TIT::x=y,ans+=ask(rt[x],1,n);
		return ans;
	}
}

int main(){
	n=nxi(),m=nxi(),ol=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=1; i<n; ++i){
		int x=nxi(),y=nxi();
		G::add(x,y,nxi());
	}
	G::kruskal();
	G::dfs_dfn(1);
	KST::build();
	lint ans=ol-1;
	for(int i=1; i<=m; ans=ol?ans:-1,++i){
		if(nxi()==1){
			int x=(nxi()+ans)%n+1;
			ans=val[x]+TIT::qry(KST::pfn[x],G::dfn[x]);
			printf("%lld\n",ans);
		}else{
			int v=nxi(),d=nxi(),x=(nxi()+ans)%n+1;
			int kl,kr,gl,gr;
			KST::getrng(x,d,kl,kr);
			G::getrng(x,gl,gr);
			TIT::mdf(kl,kr,gl,gr,v);
		}
	}
	eprintf("%d\n",TIT::cnt);
	return 0;
}
