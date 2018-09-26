#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
const int N=3e5+2;
int n,m,cup,cdwn,sz[N],fa[N],gcy[N],chk[N],dep[N],dfn[N],ans[N];
struct data{
	int v,x,t;
	bool operator < (const data &b) const {
		return t<b.t;
	}
}qup[N<<1],qdwn[N<<1];

bool gcy_cmp_up(const int a,const int b){
	return dep[a]+chk[a]<dep[b]+chk[b];
}

bool gcy_cmp_dwn(const int a,const int b){
	return chk[a]-dep[a]<chk[b]-dep[b];
}

inline char get_c(){
	static char *h,*t,buf[20000];
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=get_c())>'9'||c<'0');
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,cnd,son[N],fir[N],top[N];
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
			if(!sz[y]){
				fa[y]=x;
				dep[y]=dep[x]+1;
				dfs1(y);
				if(sz[y]>sz[son[x]]) son[x]=y;
				sz[x]+=sz[y];
			}
		}
	}

	void dfs2(const int x,const int tp){
		dfn[x]=++cnd;
		top[x]=tp;
		if(son[x]) dfs2(son[x],top[x]);
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!dfn[y]) dfs2(y,y);
		}
	}

	inline int get_lca(int x,int y){
		while(top[x]!=top[y]){
			if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
			else y=fa[top[y]];
		}
		return dep[x]<dep[y]?x:y;
	}
}

namespace T{
	int tr[N];

	inline void mod(int x,const int v){
		for(;x<=n;x+=x&-x){
			tr[x]+=v;
		}
	}

	inline int ask(int x){
		int ans=0;
		for(;x;x-=x&-x){
			ans+=tr[x];
		}
		return ans;
	}

	inline int ask(const int x,const int y){
		return ask(y)-ask(x-1);
	}
}

inline void solve(int q,data dt[N<<1],const int f){
	for(int i=1,k=1,l=1;i<=n&&k<=q;){
		for(;i<=n&&chk[gcy[i]]+dep[gcy[i]]*f<dt[k].t;++i);
		for(l=k;l<=q&&dt[l].t==dt[k].t;++l){
			T::mod(dfn[dt[l].x],dt[l].v);
		}
		for(;i<=n&&chk[gcy[i]]+dep[gcy[i]]*f==dt[k].t;++i){
			ans[gcy[i]]+=T::ask(dfn[gcy[i]],dfn[gcy[i]]+sz[gcy[i]]-1);
		}
		for(;k<l&&k<=q;++k){
			T::mod(dfn[dt[k].x],-dt[k].v);
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("b.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<n;++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	for(int i=1;i<=n;++i){
		chk[i]=nxi();
		gcy[i]=i;
	}
	G::dfs1(1);
	G::dfs2(1,1);
	for(int i=1;i<=m;++i){
		const int x=nxi(),y=nxi();
		const int z=G::get_lca(x,y),ld=dep[x]-dep[z];
		qup[++cup]=(data){1,x,dep[x]};
		if(fa[z]) qup[++cup]=(data){-1,fa[z],dep[x]};
		qdwn[++cdwn]=(data){1,y,ld-dep[z]};
		qdwn[++cdwn]=(data){-1,z,ld-dep[z]};
	}
	std::sort(qup+1,qup+cup+1);
	std::sort(qdwn+1,qdwn+cdwn+1);
	std::sort(gcy+1,gcy+n+1,gcy_cmp_up);
	solve(cup,qup,1);
	std::sort(gcy+1,gcy+n+1,gcy_cmp_dwn);
	solve(cdwn,qdwn,-1);
	for(int i=1;i<=n;++i){
		printf("%d ",ans[i]);
	}
	puts("");
	return 0;
}
