#include <iostream>
#include <cstdio>
#include <cstring>
const int N=305;
int n,m,q,dp[N][N][2];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

namespace G{
	int cnt,sz[N],fir[N];
	struct edge{
		int to,wi,nx;
	}eg[N<<1];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	void dfs(const int x){
		dp[x][0][0]=dp[x][1][1]=0;
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!sz[y]){
				dfs(y);
				for(int j=sz[x]+sz[y]; ~j; --j){
					int &dp0=dp[x][j][0];
					int &dp1=dp[x][j][1];
					dp0=dp0+dp[y][0][0]+(m==2?eg[i].wi:0);
					dp1=dp1+dp[y][0][0];
					for(int k=j-1; ~k&&k+sz[y]>=j; --k){
						int bef0=dp[x][k][0];
						int bef1=dp[x][k][1];
						apn(dp0,bef0+dp[y][j-k][1]);
						apn(dp0,bef0+dp[y][j-k][0]+(m==2?eg[i].wi:0));
						apn(dp1,bef1+dp[y][j-k][0]);
						apn(dp1,bef1+dp[y][j-k][1]+eg[i].wi);
					}
				}
				sz[x]+=sz[y];
			}
		}
	}
}

int main(){
	memset(dp,1,sizeof(dp));
	n=nxi(),m=nxi(),q=nxi();
	if(q+m-1>n){
		puts("-1");
		return 0;
	}
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi(),v=nxi();
		G::add(a,b,v);
		G::add(b,a,v);
	}
	G::dfs(1);
	printf("%d\n",dp[1][q][1]);
	return 0;
}
