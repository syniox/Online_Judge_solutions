#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=2e5+10;
int n,hx[N],fa[N],dfn[N],xdn[N],nfd[N],top[N];
struct data{
	lint a,b;
	//val,hex
};

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
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
	int cnt,cnd,sz[N],dep[N],son[N],fir[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}
	void dfs1(const int x){
		sz[x]=1;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa[x]){
				dep[y]=dep[x]+1;
				fa[y]=x;
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

namespace T{
	int x,y;
	lint va,vb;
	data tr[N*3];
	inline data merge(const data &x,const data &y){
		return (data){std::min(x.a+y.a,x.b),std::min(x.a+y.b,x.b)};
	}
	inline void upd(const int k){
		tr[k]=merge(tr[k<<1],tr[k<<1|1]);
	}
	inline void build(const int k,const int l,const int r){
		if(l==r){
			tr[k]=(data){0,hx[nfd[l]]};
			return;
		}
		const int mid=(l+r)>>1;
		build(k<<1,l,mid);
		build(k<<1|1,mid+1,r);
		upd(k);
	}
	void mod(const int k,const int l,const int r){
		if(l==r){
			tr[k].a+=va;
			tr[k].b+=vb;
			return;
		}
		const int mid=(l+r)>>1;
		if(x>mid) mod(k<<1|1,mid+1,r);
		else mod(k<<1,l,mid);
		upd(k);
	}
	data ask(const int k,const int l,const int r){
		if(l>=x&&r<=y) return tr[k];
		const int mid=(l+r)>>1;
		if(y<=mid) return ask(k<<1,l,mid);
		if(x>mid) return ask(k<<1|1,mid+1,r);
		return merge(ask(k<<1,l,mid),ask(k<<1|1,mid+1,r));
	}
	inline void mod_t(const int x,const lint va,const lint vb){
		T::x=x,T::va=va,T::vb=vb;
		mod(1,1,n);
	}
	inline data ask_t(const int x,const int y){
		T::x=x,T::y=y;
		return ask(1,1,n);
	}
}

inline void get_son_hex(const int x){
	using namespace G;
	lint cur=0;
	for(int i=fir[x];i;i=eg[i].nx){
		const int y=eg[i].to;
		if(y!=fa[x]){
			get_son_hex(y);
			if(y!=son[x]){
				cur+=T::ask_t(dfn[y],xdn[y]).b;
			}
		}
	}
	T::mod_t(dfn[x],cur,0);
}

inline void mod_g(int x,lint v){
	lint v1=T::ask_t(dfn[top[x]],xdn[x]).b;
	T::mod_t(dfn[x],0,v);
	lint v2=T::ask_t(dfn[top[x]],xdn[x]).b;
	v=v2-v1;
	while((x=fa[top[x]])&&v){
		v1=T::ask_t(dfn[top[x]],xdn[x]).b;
		T::mod_t(dfn[x],v,0);
		v2=T::ask_t(dfn[top[x]],xdn[x]).b;
		v=v2-v1;
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("c.in","r",stdin);
#endif
	n=nxi();
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
	memcpy(xdn,dfn,sizeof(dfn));
	for(int i=1;i<=n;++i){
		apx(xdn[top[i]],dfn[i]);
	}
	for(int i=1;i<=n;++i){
		apx(xdn[i],xdn[top[i]]);
	}
	T::build(1,1,n);
	get_son_hex(1);
	int q=nxi();
	while(q--){
		char c;
		while((c=getchar())!='C'&&c!='Q');
		if(c=='Q'){
			const int x=nxi();
			printf("%lld\n",T::ask_t(dfn[x],xdn[x]).b);
		}
		else{
			const int x=nxi(),v=nxi();
			mod_g(x,v);
		}
	}
	return 0;
}
