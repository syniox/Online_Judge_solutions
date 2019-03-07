#include <iostream>
#include <cstdio>
#include <cstring>
const int N=3005;
int n,val[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,fir[N];
	bool vis[N],win[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	bool dfs(const int x){
		if(vis[x]) return win[x];
		vis[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(val[y]<val[x]&&!dfs(y)) return win[x]=1;
		}
		return 0;
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	for(int i=1; i<=n; ++i){
		if(G::dfs(i)) printf("%d ",i);
	}
	puts("");
	return 0;
}
