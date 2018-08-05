//ans[y]=(dep[y]+1)*v[x]-dep[x]*v[x](dep[x]<dep[y],lca(x,y)==x);
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cassert>
const int N=2e5+2;
const int mo=2147483647;
typedef long long lint;
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

struct B_I_T{
	int tr[N];
	inline void mod(int x,int v){
		for(;x<=n;x+=x&-x){
			tr[x]=(tr[x]+v)&mo;
		}
	}
	inline void mod_t(int x,int v){
		mod(dfn[x],v);
		mod(dfn[x]+sz[x],-v);
	}
	inline int ask(int x){
		int ans=0;
		for(;x;x-=x&-x){
			ans=(ans+tr[x])&mo;
		}
		return ans;
	}
}tr1,tr2;
//1:sum 2:with dep

inline int clen(int x){
	int ans1=tr1.ask(dfn[x]),ans2=tr2.ask(dfn[x]);
	return (lint)(ans1*(dep[x]+1)-ans2)&mo;
}

inline int solve(int k){
	static int oga[5],ogb[5],zf[1<<5],_dp[1<<5],p_lca[1<<5];
	memset(zf,0,sizeof zf);
	memset(p_lca,0,sizeof p_lca);
	memset(_dp,0,sizeof _dp);
	for(int i=0;i<k;++i){
		oga[i]=nxi(),ogb[i]=nxi();
		if(dep[oga[i]]<dep[ogb[i]]) std::swap(oga[i],ogb[i]);
	}
	for(int i=0;i<k;++i){
		p_lca[1<<i]=oga[i];
		_dp[1<<i]=ogb[i];
		zf[1<<i]=1;
	}
	int ans=0;
	for(int i=1;i<1<<k;++i){
		int lt=i&-i;
		if(!p_lca[i]){
			p_lca[i]=lca(p_lca[i^lt],p_lca[lt]);
			_dp[i]=dep[_dp[i^lt]]>dep[_dp[lt]]?_dp[i^lt]:_dp[lt];
			zf[i]=-zf[i^lt];
		}
		if(dep[p_lca[i]]>=dep[_dp[i]]){
			ans=(ans+zf[i]*(clen(p_lca[i])-clen(fa[_dp[i]])))&mo;
		}
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen(".in","r",stdin);
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
		if(op) printf("%d\n",solve(k));
		else{
			int v=nxi();
			tr1.mod_t(k,v);
			tr2.mod_t(k,(lint)v*dep[k]&mo);
		}
	}
	return 0;
}
