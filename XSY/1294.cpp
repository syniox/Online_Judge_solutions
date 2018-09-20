#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1e5+2;
//xdn: max dfn on the chain
int n,m,cnf,sz[N],hx[N],fa[N];
int dep[N],xdn[N],dfn[N],nfd[N],top[N],rk_top[N],fk_top[N];
bool vis[N];

inline void apx(int &x,const int y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while(((c=getchar())>'9'||c<'0')&&c!='-');
	const bool f=c=='-'&&(c=getchar());
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return f?-x:x;
}

namespace G{
	int cnt,cnd,son[N],fir[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs1(const int x){
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa[x]){
				fa[y]=x;
				dep[y]=dep[x]+1;
				dfs1(y);
				if(sz[y]>sz[son[x]]) son[x]=y;
				sz[x]+=sz[y];
			}
		}
	}

	void dfs2(const int x){
		dfn[x]=++cnd;
		nfd[cnd]=x;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		if(son[x]) dfs2(son[x]);
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!dfn[y]) dfs2(y);
		}
	}
}


namespace R{
	int x,v,tr[N*3];

	inline void upd(const int k){
		tr[k]=std::max(tr[k<<1],tr[k<<1|1]);
	}

	inline void mod(const int k,const int l,const int r){
		if(l==r){
			tr[k]+=v;
			return;
		}
		const int mid=(l+r)>>1;
		if(x>mid) mod(k<<1|1,mid+1,r);
		else mod(k<<1,l,mid);
		upd(k);
	}

	inline void mod_t(const int x,const int v){
		R::x=x,R::v=v;
		mod(1,1,cnf);
	}
}

namespace T{
	int x,y,v;
	struct node{
		int ls,rs,ms,s;
	}tr[N*3];

	inline void tr_set(const int k,const int v){
		tr[k].s=v;
		tr[k].ls=tr[k].rs=tr[k].ms=std::max(0,v);
	}

	inline node merge(const node &x,const node &y){
		node ans;
		ans.s=x.s+y.s;
		ans.ls=std::max(x.ls,x.s+y.ls);
		ans.rs=std::max(y.rs,y.s+x.rs);
		ans.ms=std::max(x.ms,y.ms);
		apx(ans.ms,x.rs+y.ls);
		return ans;
	}

	inline void upd(const int k){
		tr[k]=merge(tr[k<<1],tr[k<<1|1]);
	}

	inline void build(const int k,const int l,const int r){
		if(l==r){
			tr_set(k,hx[nfd[l]]);
			return;
		}
		const int mid=(l+r)>>1;
		build(k<<1,l,mid);
		build(k<<1|1,mid+1,r);
		upd(k);
	}

	inline node ask(const int k,const int l,const int r){
		if(l>=x&&r<=y) return tr[k];
		const int mid=(l+r)>>1;
		if(x>mid) return ask(k<<1|1,mid+1,r);
		if(y<=mid) return ask(k<<1,l,mid);
		return merge(ask(k<<1,l,mid),ask(k<<1|1,mid+1,r));
	}

	inline void mod(const int k,const int l,const int r){
		if(l==r){
			tr_set(k,tr[k].s+v);
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid) mod(k<<1,l,mid);
		else mod(k<<1|1,mid+1,r);
		upd(k);
	}

	inline void mod_t(const int x,const int v){
		T::x=x,T::v=v;
		mod(1,1,n);
	}

	inline node ask_t(const int x,const int y){
		T::x=x,T::y=y;
		return ask(1,1,n);
	}
}

inline void get_son_hex(const int x){
	using namespace G;
	for(int i=fir[x];i;i=eg[i].nx){
		const int y=eg[i].to;
		if(y!=fa[x]&&y!=son[x]){
			get_son_hex(y);
			T::mod_t(dfn[x],T::ask_t(dfn[y],xdn[y]).ls);
		}
	}
}

inline void mod_g(int x,const int v){
	int delta=v-hx[x];
	for(;x;x=fa[top[x]]){
		const T::node v1=T::ask_t(dfn[top[x]],xdn[top[x]]);
		T::mod_t(dfn[x],delta);
		const T::node v2=T::ask_t(dfn[top[x]],xdn[top[x]]);
		delta=v2.ls-v1.ls;
		R::mod_t(rk_top[top[x]],v2.ms-v1.ms);
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=n;++i){
		hx[i]=nxi();
	}
	for(int i=1;i<n;++i){
		const int x=nxi(),y=nxi();
		G::add(x,y);
		G::add(y,x);
	}
	G::dfs1(1);
	G::dfs2(1);
	for(int i=1;i<=n;++i){
		if(!vis[top[i]]){
			vis[top[i]]=1;
			rk_top[top[i]]=++cnf;
			fk_top[cnf]=top[i];
		}
		apx(xdn[top[i]],dfn[i]);
	}
	T::build(1,1,n);
	get_son_hex(1);
	for(int i=1;i<=cnf;++i){
		const int x=fk_top[i];
		R::mod_t(i,T::ask_t(dfn[x],xdn[x]).ms);
	}
	for(int i=1;i<=m;++i){
		const int op=nxi();
		if(op==2) printf("%d\n",R::tr[1]);
		else{
			const int x=nxi(),v=nxi();
			mod_g(x,v);
		}
	}
	return 0;
}
