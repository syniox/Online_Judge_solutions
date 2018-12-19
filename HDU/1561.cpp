#include <iostream>
#include <cstdio>
#include <cstring>
const int N=205;
int n,m,hx[N],dp[N][N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,cnd,sz[N],dfn[N],fir[N],que[N];
	struct edge{
		int to,nx;
	}eg[N];

	inline void init(){
		cnt=cnd=0;
		memset(fir,0,sizeof(fir));
	}

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs(const int x){
		dfn[x]=++cnd;
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			dfs(eg[i].to);
			sz[x]+=sz[eg[i].to];
		}
	}
}

int main(){
	for(n=nxi(),m=nxi(); n&&m; n=nxi(),m=nxi()){
		++m;
		memset(dp,0,sizeof(dp));
		G::init();
		for(int i=1; i<=n; ++i){
			G::add(nxi(),i);
			hx[i]=nxi();
		}
		G::dfs(0);
		for(int i=0; i<=n; ++i){
			G::que[G::dfn[i]]=i;
		}
		for(int i=n+1; i; --i){
			const int x=G::que[i];
			for(int j=m; j; --j){
				dp[i][j]=std::max(dp[i+G::sz[x]][j],dp[i+1][j-1]+hx[x]);
			}
		}
		printf("%d\n",dp[1][m]);
	}
	return 0;
}
