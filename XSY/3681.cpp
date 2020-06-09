#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e5+5;
int n,m,val[N];
bool ol;

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

namespace KST{
	int cnt,fir[N<<1],fa[N<<1],val[N<<1],val_d[N<<1],nsum[N<<1];
	int sz[N<<1],son[N<<1],top[N<<1],dfn[N<<1],idx[N<<1];
	struct edge{
		int to,nx;
	}eg[N<<1];
	inline void add(const int a,const int b){
		fa[b]=a;
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs_top(const int x){
		static int cnd;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		val_d[dfn[x]=++cnd]=val[x];
		idx[cnd]=x;
		nsum[cnd]=nsum[cnd-1]+(x<=n);
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

	void getrng(int x,const int d,int &x,int &y){
		assert(x<=n);
		for(; val[fa[top[x]]]>=d; x=fa[top[x]]);
		int l=dfn[top[x]],r=dfn[x],mid;
		while(l!=r){
			mid=(l+r)>>1;
			if(val_d[mid]<d) l=mid+1;
			else r=mid;
		}
		l=idx[l],r=dfn[l]+sz[l]-1,l=dfn[l];
		x=nsum[l-1]+1,y=nsum[r];
	}
}

namespace G{
	int cnt,fir[N],dfn[N];
	struct edge{
		int to,nx;
	}eg[N<<1];
	struct eg2{
		int a,b,v;
		friend bool operator < (const eg2 &a,const eg2 &b){
			return a.v<b.v;
		}
	}e[N];
	inline void add(const int a,const int b,const int v){
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
	void dfs_dfn(const int x){
		static int cnd;
		dfn[x]=++cnd;
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!dfn[y]) dfs_dfn(y),sz[x]+=sz[y];
		}
	}
	void getrng(const int x,int &l,int &r){
		l=dfn[x],r=dfn[x]+sz[x]-1;
	}
}

namespace KDT{
	int rt,idx[N];
	bool curd;
	struct node{
		int id,v[2],wx[2],wn[2],ls,rs,fa;
		lint tag;
		friend bool operator < (node &a,node &b){
			return a.v[curd]<b.v[curd];
		}
	}tr[N<<1];
	void upd(const int k){
		int ls=tr[k].ls,rs=tr[k].rs;
	}
	int build_tr(const int l,const int r){
		const int mid=(l+r+1)>>1;
		std::nth_element(tr+l,tr+mid,tr+r);
		curd^=1;
		int ls=l==mid?0:build_tr(l,mid-1);
		int rs=r==mid?0:build_tr(mid+1,r);
		if(ls) tr[tr[mid].ls=ls].fa=mid;
		if(rs) tr[tr[mid].rs=rs].fa=mid;
		upd(mid);
		curd^=1;
	}
	void build(){
		for(int i=1; i<=n; ++i){
			int dg=G::dfn[i],dk=KST::nsum[KST::dfn[i]];
			tr[i]=(node){i,[dg,dk]};
		}
		rt=build_tr(1,n);
	}
	lint qry(int x){
		lint ans=0;
		for(; x; x=tr[x].fa){
			ans+=tr[x].tag;
		}
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
	KDT::build();
	for(int i=1; i<=n; ++i){
		if(nxi()==1){
			KDT::qry(nxi());
		}else{

		}
	}
	return 0;
}
