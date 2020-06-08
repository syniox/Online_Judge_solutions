#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e5+5;
int n,m,val[N];

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
	bool tr[N];
	inline void rev(int x){
		for(; x<=n; x+=x&-x) tr[x]^=1;
	}
	inline void revseg(const int l,const int r){
		rev(l),rev(r+1);
	}
	inline bool ask(int x){
		bool ans=0;
		for(; x; x-=x&-x) ans^=tr[x];
		return ans;
	}
}

namespace T{
	int x,y,v;
	bool f;
	struct node{
		int un,ux,dn,dx;
		//最小上界，最大上界，最小下界，最大下界(闭区间)
		bool rev;
		node(){
			un=ux=dn=dx=-1;
			rev=0;
		}
		void getrev(){
			rev^=1;
			std::swap(dn,un);
			std::swap(dx,ux);
		}
		void set(const int v,const bool f){
			un=ux=dn=dx=-1;
			if(f==1) dn=dx=v+1;
			else un=ux=v-1;
		}
		friend node operator * (const node &a,const node &b){
			node c;
			if(a.un==-1||b.un==-1)
				c.un=a.un&b.un,c.ux=a.ux&b.ux;
			else{
				c.un=std::min(a.un,b.un);
				c.ux=std::max(a.ux,b.ux);
			}
			if(a.dn==-1||b.dn==-1)
				c.dn=a.dn&b.dn,c.dx=a.dx&b.dx;
			else{
				c.dn=std::min(a.dn,b.dn);
				c.dx=std::max(a.dx,b.dx);
			}
			return c;
		}
	}tr[N];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}
	inline void set(const int x,const int v,const bool f){
		tr[idx(x,x)].set(v,f);
	}
	inline void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		tr[idx(l,r)]=tr[idx(l,mid)]*tr[idx(mid+1,r)];
	}

	void psh(const int l,const int r){
		assert(l!=r);
		bool &rev=tr[idx(l,r)].rev;
		const int mid=(l+r)>>1;
		if(!rev) return;
		tr[idx(l,mid)].getrev();
		tr[idx(mid+1,r)].getrev();
		rev=0;
	}

	void build(const int l,const int r){
		if(l==r) return;
		const int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
		tr[idx(l,r)]=tr[idx(l,mid)]*tr[idx(mid+1,r)];
	}

	void apl_t(const int l,const int r){
		if(l==r){
			tr[idx(l,r)].set(v,f);
			return;
		}
		psh(l,r);
		const int mid=(l+r)>>1;
		if(x<=mid) apl_t(l,mid);
		else apl_t(mid+1,r);
		upd(l,r);
	}

	node ask_t(const int l,const int r){
		if(l>=x&&r<=y) return tr[idx(l,r)];
		psh(l,r);
		const int mid=(l+r)>>1;
		node p;
		if(x<=mid) p=p*ask_t(l,mid);
		if(x>mid) p=p*ask_t(mid+1,r);
		return p;
	}

	void revseg_t(const int l,const int r){
		if(l>=x&&r<=y){
			tr[idx(l,r)].getrev();
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) revseg_t(l,mid);
		if(y>mid) revseg_t(mid+1,r);
		upd(l,r);
	}

	inline void apl(const int x,const int v,const int f){
		T::x=x,T::v=v,T::f=f;
		apl_t(1,n);
	}
	inline node ask(const int x,const int y){
		T::x=x,T::y=y;
		return ask_t(1,n);
	}
	inline void revseg(const int x,const int y){
		T::x=x,T::y=y;
		return revseg_t(1,n);
	}
}

namespace G{
	int rt,ch[N][2];
	int sz[N],fa[N],top[N],dep[N],dfn[N],son[N];
	bool nrt[N];

	void dfs_son(const int x){
		sz[x]=1;
		for(int i=0; i<2; ++i){
			const int y=ch[x][i];
			if(!y) continue;
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
		if(fa[x]) T::set(dfn[x],val[fa[x]],ch[fa[x]][1]==x);
		if(!son[x]) return;
		dfs_top(son[x]);
		for(int i=0; i<2; ++i){
			if(!dfn[ch[x][i]]) dfs_top(ch[x][i]);
		}
	}

	void pshrev(const int x){
		int l=dfn[x],r=dfn[x]+sz[x]-1;
		B::revseg(l,r);
		T::revseg(l,r);
	}

	bool ask(const int x){
		T::node p;
		for(int i=x; i; i=fa[top[i]]){
			p=p*T::ask(dfn[top[i]],dfn[i]);
		}
		if(~p.dx&&val[x]<p.dx) return 0;
		if(~p.un&&val[x]>p.un) return 0;
		return 1;
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		G::nrt[G::ch[i][0]=nxi()]=1;
		G::nrt[G::ch[i][1]=nxi()]=1;
	}
	for(G::rt=1; G::nrt[G::rt]; ++G::rt);
	G::dfs_son(G::rt);
	G::dfs_top(G::rt);
	T::build(1,n);
	for(int op,i=1; i<=m; ++i){
		if((op=nxi())==1){
			int x=nxi(),v=nxi(),rev=B::ask(G::dfn[x]);
			int ls=G::ch[x][rev],rs=G::ch[x][rev^1];
			val[x]=v;
			if(ls) T::apl(G::dfn[ls],v,rev);
			if(rs) T::apl(G::dfn[rs],v,rev^1);
		}else if(op==2){
			G::pshrev(nxi());
		}else{
			puts(G::ask(nxi())?"YES":"NO");
		}
	}
	return 0;
}
