#include<iostream>
#include<cstdio>
#include<cstring>
#define ni nxi<int>()
typedef unsigned long long ull;
const int N=1e5+2;
int n,m,bit,op[N],fa[N],hx[N],dep[N],dfn[N],nfd[N],top[N];
//&1,|2,^3
struct node{
	//s:up v:down
	ull s0,s1,v0,v1;
};

template <class T> inline T nxi(){
	T x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}
//calc:graph
inline ull calc(const ull x,const int k){
	if(op[k]==1) return x&k;
	if(op[k]==2) return x|k;
	return x^k;
}

inline node merge(const node x,const node y){
	node ans;
	ans.s0=(x.s0&y.s1)|(~x.s0&y.s0);
	ans.s1=(x.s1&y.s1)|(~x.s1&y.s0);
	ans.v0=(y.v0&x.v1)|(~y.v0&x.v0);
	ans.v1=(y.v1&x.v1)|(~y.v1&x.v0);
	return ans;
}

inline int highbit(ull x){
	int ans=0;
	if(x>>32) x>>=32,ans+=32;
	if(x>>16) x>>=16,ans+=16;
	if(x>>8) x>>=8,ans+=8;
	if(x>>4) x>>=4,ans+=4;
	if(x>>2) x>>=2,ans+=2;
	if(x>>1) x>>=1,ans+=1;
	return ans;
}

namespace G{
	int sz[N],son[N],fir[N];
	struct edge{
		int to,nx;
	}eg[N<<1];
	inline void add(int x,int y){
		static int cnt;
		eg[++cnt]=(edge){y,fir[x]};
		fir[x]=cnt;
	}
	void dfs1(int x){
		sz[x]=1;
		for(int i=fir[x];i;i=eg[i].nx){
			int y=eg[i].to;
			if(!sz[y]){
				dep[y]=dep[x]+1;
				fa[y]=x;
				dfs1(y);
				if(sz[y]>sz[son[x]]) son[x]=y;
				sz[x]+=sz[y];
			}
		}
	}
	void dfs2(int x){
		static int cnt;
		dfn[x]=++cnt;
		nfd[cnt]=x;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		if(son[x]) dfs2(son[x]);
		for(int i=1;i<=n;++i){
			int y=eg[i].to;
			if(!dfn[y]) dfs2(y);
		}
	}
}

namespace T{
	int x,y;
	node tr[N*3];
	inline void upd(int k){
		tr[k]=merge(tr[k<<1],tr[k<<1|1]);
	}
	void build(int k,int l,int r){
		if(l==r){
			tr[k].v0=tr[k].s0=calc(0,nfd[l]);
			tr[k].v1=tr[k].s1=calc(1,nfd[l]);
			return;
		}
		int mid=(l+r)>>1;
		build(k<<1,l,mid);
		build(k<<1|1,mid+1,r);
		upd(k);
	}
	void mod(int k,int l,int r){
		if(l==r){
			tr[k].v0=tr[k].s0=calc(0,nfd[l]);
			tr[k].v1=tr[k].s1=calc(1,nfd[l]);
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid) mod(k<<1,l,mid);
		else mod(k<<1|1,mid+1,r);
		upd(k);
	}
	node ask(int k,int l,int r){
		if(l>=x&&r<=y) return tr[k];
		int mid=(l+r)>>1;
		if(x>mid) return ask(k<<1|1,mid+1,r);
		if(y<=mid) return ask(k<<1,l,mid);
		return merge(ask(k<<1,l,mid),ask(k<<1|1,mid+1,r));
	}
}

inline ull ask_G(int x,int y,ull z){
	node getx,gety;
	const ull ff=~(ull)0;
	getx=gety=(node){ff,ff,ff,ff};
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]){
			T::x=dfn[top[x]],T::y=dfn[x];
			getx=merge(getx,T::ask(1,1,n));
			x=fa[top[x]];
		}else{
			T::x=dfn[top[y]],T::y=dfn[y];
			gety=merge(gety,T::ask(1,1,n));
			y=fa[top[y]];
		}
	}
	if(dep[x]>dep[y]){
		T::x=dfn[y],T::x=dfn[x];
		getx=merge(getx,T::ask(1,1,n));
	}
	else{
		T::x=dfn[x],T::y=dfn[y];
		gety=merge(gety,T::ask(1,1,n));
	}

	ull ans0=(getx.s0&gety.v1)|(~getx.s0&gety.v0);
	ull ans1=(getx.s1&gety.v1)|(~getx.s1&gety.v0);
	int i=highbit(z);
	ull ans=0;
	bool f=0;
	for(;i>=0;--i){
		if(ans0&(1ll<<i)){
			if(z&(1ll<<i)) f=1;
			ans|=(1ll<<i);
		}
		else if(ans1&(1ll<<i)){
			if(f||(z&(1ll<<i))) ans|=(1ll<<i);
		}
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	n=ni,m=ni,bit=ni;
	for(int i=1;i<=n;++i){
		op[i]=ni,hx[i]=ni;
	}
	for(int i=1;i<n;++i){
		int x=ni,y=ni;
		G::add(x,y);
		G::add(y,x);
	}
	G::dfs1(1);
	G::dfs2(1);
	T::build(1,1,n);
	while(m--){
		int q=ni,x=ni,y=ni,z=nxi<ull>();
		if(q==1) printf("%lld\n",ask_G(x,y,z));
		else{
			op[x]=y,hx[x]=z;
			T::x=x;
			T::mod(1,1,n);
		}
	}
	return 0;
}
