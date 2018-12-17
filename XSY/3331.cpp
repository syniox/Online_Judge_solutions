#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=1e5+5;
//0: up->down:increase 1: up->down:decrease
int n,hx[N];
lint dp[N][2];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())<'0'||c>'9');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,fir[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs(const int x,const int fa){
		lint res=0;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa){
				dfs(y,x);
				res+=std::max(dp[y][0],dp[y][1]);
			}
		}
		dp[x][0]=dp[x][1]=res;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa) continue;
			lint cos=std::max(dp[y][0],dp[y][1]);
			apx(dp[x][1],res-cos+dp[y][1]+hx[x]-hx[y]);
			apx(dp[x][0],res-cos+dp[y][0]+hx[y]-hx[x]);
		}
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		hx[i]=nxi();
	}
	for(int i=1; i<n; ++i){
		const int x=nxi(),y=nxi();
		G::add(x,y);
		G::add(y,x);
	}
	G::dfs(1,0);
	printf("%lld\n",std::max(dp[1][0],dp[1][1]));
	return 0;
}
