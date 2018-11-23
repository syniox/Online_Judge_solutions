#include <iostream>
#include <cstdio>
#include <cstring>
const int N=5005;
int n,q;

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
	int cnt,res,ans,fir[N],dep[N];
	bool vis[N];
	struct edge{
		int to,nx;
	}eg[N];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}
	inline void init(){
		res=0;
		memset(vis,0,sizeof(vis));
		memset(dep,1,sizeof(dep));
	}

	inline void dfs(const int x){
		vis[x]=1;
		res+=dep[x]>q>>1;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!vis[y]){
				apn(dep[y],dep[x]+1);
				dfs(y);
			}
		}
	}
	inline void solve(){
		ans=1e9;
		for(int i=1;i<=n;++i){
			init();
			dep[i]=0;
			dfs(i);
			apn(ans,res);
		}
		++q;
		for(int i=1;i<=n;++i){
			for(int j=fir[i];j;j=eg[j].nx){
				const int k=eg[j].to;
				if(i<k){
					init();
					dep[i]=dep[k]=1;
					dfs(i);
					apn(G::ans,G::res);
				}
			}
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("c.in","r",stdin);
#endif
	n=nxi(),q=nxi();
	for(int i=1;i<n;++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	G::solve();
	printf("%d\n",G::ans);
	return 0;
}
