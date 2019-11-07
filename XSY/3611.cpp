#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
typedef long long lint;
const int N=2e5+5;
const int mod=998244353;
int n,val[N],ans=1;
double dp[N][2];

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

namespace G{
	int cnt,fir[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs_dp(const int x,const int f){
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==f) continue;
			dfs_dp(y,x);
			dp[x][0]+=std::max(dp[y][0],dp[y][1]);
			dp[x][1]+=dp[y][0];
		}
		dp[x][1]+=log(val[x]);
	}

	void dfs_ans(const int x,const int f,const bool lim){
		bool use=lim==1&&dp[x][1]>dp[x][0];
		if(use) ans=(lint)ans*val[x]%mod;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=f) dfs_ans(y,x,use^1);
		}
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
	G::dfs_dp(1,1);
	G::dfs_ans(1,1,1);
	printf("%d\n",ans);
	return 0;
}
