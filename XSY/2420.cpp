#include <iostream>
#include <cstdio>
#include <cstring>
const int N=3005;
int n,m;
unsigned hash[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

namespace G{
	int cnt=1,fir[N];
	int cnf,cnd,down,sz[N],dfn[N],low[N],bel[N];
	bool vis[N],otq[N];
	struct edge{
		int to,nx;
	}eg[N*3];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	int dfs_sz(const int x){
		int sz=1;
		vis[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!vis[y]) sz+=dfs_sz(y);
		}
		return sz;
	}

	void tarjan(const int x,const int f){
		static int stk[N],top;
		dfn[x]=low[x]=++cnd;
		stk[++top]=x;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(down==i>>1||y==f) continue;
			if(dfn[y]){
				if(!otq[y]) apn(low[x],dfn[y]);
			}
			else{
				tarjan(y,x);
				apn(low[x],low[y]);
			}
		}
		if(dfn[x]==low[x]){
			++cnf;
			for(int j=stk[top--]; ; j=stk[top--]){
				++sz[cnf];
				bel[j]=cnf;
				otq[j]=1;
				if(j==x) break;
			}
		}
	}

	void get_bel(){
		memset(otq+1,0,n*sizeof(bool));
		memset(sz+1,0,n*sizeof(int));
		memset(dfn+1,0,n*sizeof(int));
		cnf=0;
		for(int i=1; i<=n; ++i){
			if(!dfn[i]) tarjan(i,i);
		}
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=m; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	int ans=0;
	for(int i=1; i<=n; ++i){
		if(!G::vis[i]){
			int sz=G::dfs_sz(i);
			ans+=sz*(sz-1)>>1;
		}
	}
	G::get_bel();
	for(int i=1; i<=G::cnf; ++i){
		ans+=G::sz[i]*(G::sz[i]-1)>>1;
	}
	for(int i=1; i<=m; ++i){
		G::down=i;
		G::get_bel();
		for(int j=1; j<=n; ++j){
			hash[j]=hash[j]*(unsigned)N+(unsigned)G::bel[j];
		}
	}
	for(int i=1; i<=n; ++i){
		for(int j=i+1; j<=n; ++j){
			ans+=hash[i]==hash[j];
		}
	}
	printf("%d\n",ans);
	return 0;
}
