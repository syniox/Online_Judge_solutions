#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=105;
int n,m,q,dis[N][1<<10],dp[1<<10];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

inline bool check(int t){
	for(; t; t>>=2){
		if((t&3)!=3&&(t&3)) return 0;
	}
	return 1;
}

namespace G{
	int cnt,fir[N];
	struct edge{
		int to,wi,nx;
	}eg[2005];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	void dij(const int t){
		static bool vis[N];
		memset(vis,0,sizeof(vis));
		for(int i=1; i<=n; ++i){
			int x=1;
			for(int j=2; j<=n; ++j){
				if(!vis[j]&&(vis[x]||dis[j][t]<dis[x][t])) x=j;
			}
			assert(!vis[x]);
			if(dis[x][t]>1e8) break;
			vis[x]=1;
			for(int j=fir[x]; j; j=eg[j].nx){
				const int y=eg[j].to;
				apn(dis[y][t],dis[x][t]+eg[j].wi);
			}
		}
	}
}

int main(){
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1; i<=m; ++i){
		int a=nxi(),b=nxi(),v=nxi();
		G::add(a,b,v);
		G::add(b,a,v);
	}
	memset(dis,10,sizeof(dis));
	for(int i=1; i<=n; ++i){
		if(i<=q) dis[i][1<<(i-1)]=0;
		else dis[i][0]=0;
	}
	for(int i=1; i<1<<q; ++i){
		for(int j=1; j<=n; ++j){
			for(int k=(i-1)&i; k>(i^k); k=(k-1)&i){
				apn(dis[j][i],dis[j][k]+dis[j][i^k]);
			}
		}
		G::dij(i);
	}
	for(int i=1; i<1<<q; ++i){
		if(!check(i)) continue;
		int res=1e9;
		for(int j=1; j<=n; ++j){
			apn(res,dis[j][i]);
		}
		for(int j=(i-1)&i; j>(i^j); j=(j-1)&i){
			if(check(j))
				apn(res,dp[j]+dp[i^j]);
		}
		dp[i]=res;
	}
	printf("%d\n",dp[(1<<q)-1]<1e8?dp[(1<<q)-1]:-1);
	return 0;
}
