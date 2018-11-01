#include <iostream>
#include <cstdio>
#include <cstring>
const int N=1e5+2;
int n,m,q,cnf,col[N<<1],bel[N<<1];
bool eve[N<<1];

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt=1,fir[N],dfn[N],low[N];
	struct edge{
		int fr,to,nx;
	}eg[N<<1];

	inline void add_edge(const int a,const int b){
		eg[++cnt]=(edge){a,b,fir[a]};
		fir[a]=cnt;
	}

	void tarjan(const int x,const int e){
		static int cnd,top,stk[N<<1];
		low[x]=dfn[x]=++cnd;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(dfn[y]){
				if(e!=(i^1)){
					apn(low[x],dfn[y]);
					stk[++top]=i;
				}
			}
			else{
				stk[++top]=i;
				tarjan(y,i);
			}
			apn(low[x],low[y]);
		}
		if(low[x]==dfn[x]){
			++cnf;
			int j=-1;
			while(top&&j!=e){
				j=stk[top--];
				bel[j]=bel[j^1]=cnf;
			}
		}
	}

	bool paint(const int x,const int e){
		for(int i=fir[x];i;i=eg[i].nx){
			if(bel[i]!=bel[e]) continue;
			if(~col[i]){
				if(col[i]==col[e]) return 0;
			}
			else{
				col[i]=col[e]^1;
				paint(eg[i].to,i);
			}
		}
		return 1;
	}
}

namespace T{
	int dep[N],rt[N],fa[18][N];
	bool exi[18][N],vis[N];

	void dfs(const int x){
		using G::fir;
		using G::eg;
		vis[x]=1;
		for(int i=1;i<18&&fa[i-1][x];++i){
			fa[i][x]=fa[i-1][fa[i-1][x]];
		}
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!vis[y]){
				fa[0][y]=x;
				dep[y]=dep[x]+1;
				rt[y]=rt[x];
				dfs(y);
			}
		}
	}

	void build(){
		for(int i=1;i<18;++i){
			for(int j=1;j<=n;++j){
				exi[i][j]=exi[i-1][j]|exi[i-1][fa[i-1][j]];
			}
		}
	}

	inline int lca(int x,int y){
		if(dep[x]<dep[y]) std::swap(x,y);
		int dis=dep[x]-dep[y];
		for(int i=0;i<18;++i){
			if(dis&(1<<i)) x=fa[i][x];
		}
		if(x==y) return x;
		for(int i=17;i;--i){
			if(fa[i][x]!=fa[i][y]){
				x=fa[i][x];
				y=fa[i][y];
			}
		}
		return fa[0][x];
	}

	inline bool get_exi(int x,int f){
		bool res=0;
		int dis=dep[x]-dep[f];
		for(int i=17;i&&!res;--i){
			if(dis&(1<<i)){
				res|=exi[i][x];
				x=fa[i][x];
			}
		}
		return res;
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	memset(col,-1,sizeof(col));
	n=nxi(),m=nxi();
	for(int i=1;i<=m;++i){
		const int a=nxi(),b=nxi();
		G::add_edge(a,b);
		G::add_edge(b,a);
	}
	for(int i=1;i<=n;++i){
		if(!G::dfn[i]) G::tarjan(i,0);
	}
	for(int i=2;i<=G::cnt;++i){
		if(bel[i]&&col[i]==-1){
			if(!G::paint(G::eg[i].to,i)) eve[bel[i]]=1;
		}
	}
	for(int i=1;i<=n;++i){
		if(!T::dep[i]) T::rt[i]=i,T::dfs(i);
	}
	for(int i=2;i<=G::cnt;++i){
		using G::eg;
		using T::fa;
		if(eve[bel[i]]){
			const int x=eg[i].fr,y=eg[i].to;
			if(fa[0][x]!=y&&fa[0][y]!=x) continue;
			T::exi[0][fa[0][x]==y?x:y]=1;
		}
	}
	T::build();
	q=nxi();
	while(q--){
		const int x=nxi(),y=nxi();
		if(T::rt[x]!=T::rt[y]){
			puts("No");continue;
		}
		const int z=T::lca(x,y);
		if((T::dep[x]+T::dep[y]-(T::dep[z]>>1))&1) puts("Yes");
		else puts(T::get_exi(x,z)||T::get_exi(y,z)?"Yes":"No");
	}
	return 0;
}
