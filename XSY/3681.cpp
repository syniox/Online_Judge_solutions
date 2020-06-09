#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef const int cint;
typedef long long lint;
cint N=1e5+5;
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
	int find_rt(cint x){
		return fa[x]?fa[x]=find_rt(fa[x]):x;
	}
}

namespace KST{
	int rt,cnt,fir[N<<1],fa[N<<1],val[N<<1],val_d[N<<1],nsum[N<<1];
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
			return a.v<b.v;
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

namespace KDT{
	int v,rt,idx[N],ql[2],qr[2];
	bool curd;
	struct node{
		int id,v[2],wx[2],wn[2],ls,rs,fa;
		lint tag;
		friend bool operator < (node &a,node &b){
			return a.v[curd]<b.v[curd];
		}
	}tr[N<<1];
	void upd(cint k){
		node *p=tr+k;
		int ls=tr[k].ls,rs=tr[k].rs;
		for(int i=0; i<2; ++i){
			p->wx[i]=p->wn[i]=p->v[i];
			if(ls){
				apn(p->wn[i],tr[ls].wn[i]);
				apx(p->wx[i],tr[ls].wx[i]);
			}
			if(rs){
				apn(p->wn[i],tr[rs].wn[i]);
				apx(p->wx[i],tr[rs].wx[i]);
			}
		}
	}
	bool bel(int *ql,int *qr,int *wl,int *wr){
		if(ql[0]<wl[0]||qr[0]>wr[0]) return 0;
		if(ql[1]<wl[1]||qr[1]>wr[1]) return 0;
		return 1;
	}
	bool mut(int *l1,int *r1,int *l2,int *r2){
		if(l1[0]>r2[0]||l2[0]<r1[0]) return 0;
		if(l1[1]>r2[1]||l2[1]<r1[1]) return 0;
		return 1;
	}
	int build_tr(cint l,cint r){
		cint mid=(l+r+1)>>1;
		std::nth_element(tr+l,tr+mid,tr+r);
		curd^=1;
		int ls=l==mid?0:build_tr(l,mid-1);
		int rs=r==mid?0:build_tr(mid+1,r);
		if(ls) tr[tr[mid].ls=ls].fa=mid;
		if(rs) tr[tr[mid].rs=rs].fa=mid;
		upd(mid);
		idx[tr[mid].id]=mid;
		curd^=1;
		return mid;
	}
	void mdf_t(cint k){
		if(bel(tr[k].wn,tr[k].wx,ql,qr)){
			tr[k].tag+=v;
			return;
		}
		node *ls=tr+tr[k].ls,*rs=tr+tr[k].rs;
		if(ls!=tr&&mut(ls->wn,ls->wx,ql,qr))
			mdf_t(ls-tr);
		if(rs!=tr&&mut(rs->wn,rs->wx,ql,qr))
			mdf_t(rs-tr);
	}
	void mdf(cint l0,cint r0,cint l1,cint r1,cint v){
		ql[0]=l0,qr[0]=r0,ql[1]=l1,qr[1]=r1;
		KDT::v=v;
		mdf_t(rt);
	}
	void build(){
		for(int i=1; i<=n; ++i){
			int dg=G::dfn[i],dk=KST::nsum[KST::dfn[i]];
			tr[i]=(node){i,{dg,dk}};
		}
		rt=build_tr(1,n);
	}
	lint qry(int x){
		lint ans=0;
		for(x=idx[x]; x; x=tr[x].fa){
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
	for(int ans,i=1; i<=m; ans*=ol,++i){
		if(nxi()==1){
			printf("%d\n",ans=KDT::qry((nxi()+ans-1)%n+1));
		}else{
			int v=nxi(),d=nxi(),x=(nxi()+ans-1)%n+1;
			int kl,kr,gl,gr;
			KST::getrng(x,d,kl,kr);
			G::getrng(x,gl,gr);
			KDT::mdf(kl,kr,gl,kr,v);
		}
	}
	return 0;
}
