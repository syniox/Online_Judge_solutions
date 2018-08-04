#include<iostream>
#include<cstdio>
#include<cstring>
#include<cassert>
const int N=2e5+2;
const int mo=2147483647;
int n,fa[N],sz[N],dep[N],top[N],dfn[N],p_lca[1<<5];

inline char gtc(){
	static char buf[20000],*h,*t;
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=gtc())>'9'||c<'0');
	while(x=x*10+c-48,(c=gtc())>='0'&&c<='9');
	return x;
}

namespace G{
	int fir[N],son[N];
	struct edge{
		int to,nx;
	}eg[N<<1];
	inline void add(int a,int b){
		static int cnt;
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
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
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		if(son[x]) dfs2(son[x]);
		for(int i=fir[x];i;i=eg[i].nx){
			int y=eg[i].to;
			if(!dfn[y]) dfs2(y);
		}
	}
}

inline int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
		else y=fa[top[y]];
	}
	return dep[x]<dep[y]?x:y;
}

namespace T{
	unsigned x,y,v;
	struct node{
		unsigned f,s;
	}tr[N*3];
	inline void upd(int k){
		tr[k].s=(tr[k<<1].s+tr[k<<1|1].s)&mo;
	}
	inline void psh(int k,int l,int r){
		if(tr[k].f){
			if(l!=r){
				unsigned p=tr[k].f,mid=(l+r)>>1;
				tr[k<<1].f+=p;
				tr[k<<1].s+=p*(mid-l+1);
				tr[k<<1|1].f+=p;
				tr[k<<1|1].s+=p*(r-mid);
			}
			tr[k].f=0;
		}
	}
	void mod(int k,int l,int r){
		psh(k,l,r);
		if(l>=x&&r<=y){
			tr[k].f=(tr[k].f+v)&mo;
			tr[k].s=(tr[k].s+(lint)(r-l+1)*v)&mo;
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid) mod(k<<1,l,mid);
		if(y>mid) mod(k<<1|1,mid+1,r);
		upd(k);
	}
	int ask(int k,int l,int r){
		if(l>=x&&r<=y) return tr[k].s;
		psh(k,l,r);
		int ans=0,mid=(l+r)>>1;
		if(x<=mid) ans+=ask(k<<1,l,mid);
		if(y>mid) ans+=ask(k<<1|1,mid+1,r);
		return ans;
	}
	inline void mod_t(int x,int v){
		T::x=dfn[x],T::y=dfn[x]+sz[x]-1,T::v=v;
		mod(1,1,n);
	}
	inline int ask_t(int x,int y){
		T::x=x,T::y=y;
		return ask(1,1,n);
	}
}

inline int clen(int x){
	int ans=0;
	while(x){
		ans=(ans+T::ask_t(dfn[top[x]],dfn[x]))&mo;
		x=fa[top[x]];
	}
	return ans;
}

unsigned dfs(int t,int lst,int limit){
	static int vis;
	if(t==0) return clen(p_lca[vis]);
	unsigned ans=0;
	for(int i=lst+1;i<=limit-t+1;++i){
		vis|=vis^(1<<i);
		ans=(ans+dfs(t-1,i,limit))&mo;
		vis&=vis^(1<<i);
	}
	return ans;
}

inline int solve(int k){
	static int org[5];
	for(int i=0;i<k;++i){
		int a=nxi(),b=nxi();
		if(a==1) org[i]=b;
		else org[i]=a;
	}
	memset(p_lca,0,sizeof(p_lca));
	for(int i=0;i<k;++i){
		p_lca[1<<i]=org[i];
	}
	for(int i=3;i<1<<k;++i){
		int lwbt=i&-i;
		if(!p_lca[i]){
			p_lca[i]=lca(p_lca[i^lwbt],p_lca[lwbt]);
		}
	}
	unsigned ans=0;
	for(int i=1;i<=k;++i){
		ans=(ans+(i&1?1:-1)*dfs(i,-1,k-1))&mo;
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("8.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<n;++i){
		int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	G::dfs1(1);
	G::dfs2(1);
	int q=nxi();
	while(q--){
		int op=nxi(),k=nxi();
		if(op) printf("%u\n",solve(k));
		else T::mod_t(k,nxi());
	}
	return 0;
}
