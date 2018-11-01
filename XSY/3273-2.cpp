#include <iostream>
#include <cstdio>
#include <cstring>
const int N=1e5+2;
int n,m,q,cnf,col[N],bel[N<<1];
bool eve[N<<1];

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline char get_c(){
	static char *h,*t,buf[200000];
	if(h==t){
		t=(h=buf)+fread(buf,1,200000,stdin);
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
	int cnt=1,fir[N],dfn[N],low[N];
	bool vis[N<<1];
	struct edge{
		int fr,to,nx;
	}eg[N<<1];

	inline void add_edge(const int a,const int b){
		eg[++cnt]=(edge){a,b,fir[a]};
		fir[a]=cnt;
	}

	void tarjan(const int x){
		static int cnd,top,stk[N<<1];
		low[x]=dfn[x]=++cnd;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!vis[i]) stk[++top]=i;
			if(dfn[y]){
				apn(low[x],dfn[y]);
			}
			else{
				tarjan(y);
				if(low[y]>=dfn[x]){
					int j=0;
					++cnf;
					while(j!=i){
						j=stk[top--];
						bel[j]=bel[j^1]=cnf;
						vis[j]=vis[j^1]=1;
					}
				}
				else apn(low[x],low[y]);
			}
		}
	}

	void paint(const int x){
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(~col[y]){
				if(col[y]==col[x]) eve[bel[i]]=1;
			}
			else{
				col[y]=col[x]^1;
				paint(y);
			}
		}
	}
}

namespace T{
	int cnt,dep[N],rt[N],fir[N],top[N],sz[N],son[N],fa[N],exi[N];
	struct edge{
		int to,nx;
	}eg[N];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs1(const int x){
		sz[x]=1;
		for(int i=G::fir[x];i;i=G::eg[i].nx){
			const int y=G::eg[i].to;
			if(!sz[y]){
				add(x,y);
				rt[y]=rt[x];
				fa[y]=x;
				dep[y]=dep[x]+1;
				dfs1(y);
				if(sz[y]>sz[son[x]]) son[x]=y;
				sz[x]+=sz[y];
			}
		}
	}

	void dfs2(const int x){
		exi[x]+=exi[fa[x]];
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		if(son[x]) dfs2(son[x]);
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!top[y]) dfs2(y);
		}
	}

	inline int lca(int x,int y){
		while(top[x]!=top[y]){
			if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
			else y=fa[top[y]];
		}
		return dep[x]<dep[y]?x:y;
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("d.in","r",stdin);
#endif
	memset(col,-1,sizeof(col));
	n=nxi(),m=nxi();
	for(int i=1;i<=m;++i){
		const int a=nxi(),b=nxi();
		G::add_edge(a,b);
		G::add_edge(b,a);
	}
	for(int i=1;i<=n;++i){
		if(!G::dfn[i]) G::tarjan(i);
	}
	for(int i=1;i<=n;++i){
		if(col[i]==-1) col[i]=0,G::paint(i);
	}
	for(int i=1;i<=n;++i){
		if(!T::dep[i]) T::rt[i]=i,T::dfs1(i);
	}
	for(int i=2;i<=G::cnt;++i){
		using G::eg;
		using T::fa;
		if(eve[bel[i]]){
			const int x=eg[i].fr,y=eg[i].to;
			if(fa[x]!=y&&fa[y]!=x) continue;
			T::exi[fa[x]==y?x:y]=1;
		}
	}
	for(int i=1;i<=n;++i){
		if(!T::top[i]) T::dfs2(i);
	}
	q=nxi();
	while(q--){
		const int x=nxi(),y=nxi();
		if(T::rt[x]!=T::rt[y]){
			puts("No");continue;
		}
		const int z=T::lca(x,y);
		if((T::dep[x]+T::dep[y]-(T::dep[z]<<1))&1) puts("Yes");
		else puts(T::exi[x]+T::exi[y]>T::exi[z]<<1?"Yes":"No");
	}
	return 0;
}
