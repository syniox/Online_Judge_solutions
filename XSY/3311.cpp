#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long lint;
const int N=2005;
int n,val[N];

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
	int cnt,fir[N];
	lint *work_dis,dis[N][N],dp[N][N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs_dis(int x,lint s,int f){
		work_dis[x]=s;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=f) dfs_dis(y,s+val[y],x);
		}
	}

	void dfs_dp(int x){
		static lint g_aft[N],g_bef[N];
		for(int i=1; i<=n; ++i){
			dp[x][i]=dis[x][i]+val[x];
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(dp[y][n]) continue;
			dfs_dp(y);
			g_aft[0]=1e15;
			for(int j=1,k=1; j<=n; ++j){
				g_aft[j]=g_aft[j-1];
				for(; k<=n&&dis[y][k]+val[y]<=dis[x][j]; ++k){
					apn(g_aft[j],dp[y][k]);
				}
			}
			g_bef[n+1]=1e15;
			for(int j=n,k=n; j; --j){
				g_bef[j]=g_bef[j+1];
				for(; k&&dis[y][k]>=dis[x][j]+val[x]; --k){
					apn(g_bef[j],dp[y][k]);
				}
			}
			for(int i=1; i<=n; ++i){
				dp[x][i]=dp[x][i]+std::min(g_aft[i],g_bef[i]);
			}
		}
	}

	inline lint get_ans(){
		lint ans=1e15;
		for(int i=1; i<=n; ++i){
			apn(ans,dp[1][i]);
		}
		return ans;
	}
}

int main(){
	n=nxi();
	for(int i=1; i<n; ++i){
		const int x=nxi(),y=nxi();
		G::add(x,y);
		G::add(y,x);
	}
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=1; i<=n; ++i){
		using G::dis;
		G::work_dis=dis[i];
		G::dfs_dis(i,0,0);
		std::sort(dis[i]+1,dis[i]+n+1);
	}
	G::dfs_dp(1);
	printf("%lld\n",G::get_ans());
	return 0;
}
