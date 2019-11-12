#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=55;
const int mod=998244353;
const int inv2=(mod+1)>>1;
int n,fac[N],C[N][N];

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

inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

void init(){
	for(int i=0; i<=n; ++i){
		C[i][0]=1;
		for(int j=1; j<=i; ++j){
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
		}
	}
	fac[0]=1;
	for(int i=1; i<=n; ++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
}

namespace G{
	int cnt,fir[N],sz[N],dp[N][N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs(const int x,const int f){
		//dp[x][i]: 表示x子树中每种砍i个的情况的根不换色的期望和
		static int fp[N];
		sz[x]=1,dp[x][0]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==f) continue;
			dfs(y,x);
			memset(fp,0,(sz[x]+sz[y])*sizeof(fp[0]));
			for(int lst=0,j=0; j<=sz[y]; ++j){
				int ans=(lint)lst*j%mod;
				lst=dp[y][j];
				for(int k=j+1; k<=sz[y]; ++k){
					//k为x到y连接的时间
					ans=(ans+(lint)dp[y][k-1]*inv2)%mod;
				}
				dp[y][j]=ans;
			}
			for(int i=0; i<sz[x]; ++i){
				for(int j=0; j<=sz[y]; ++j){
					const int wgt=(lint)C[i+j][i]*C[sz[x]+sz[y]-1-i-j][sz[y]-j]%mod;
					fp[i+j]=(fp[i+j]+(lint)dp[x][i]*dp[y][j]%mod*wgt)%mod;
				}
			}
			sz[x]+=sz[y];
			memcpy(dp[x],fp,sz[x]*sizeof(dp[x][0]));
		}
	}
}

int main(){
	n=nxi();
	init();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	for(int wgt=fpow(fac[n-1],mod-2),i=1; i<=n; ++i){
		memset(G::dp,0,sizeof(G::dp));
		memset(G::sz,0,sizeof(G::sz));
		G::dfs(i,i);
		printf("%lld\n",(lint)G::dp[i][0]*wgt%mod);
	}
	return 0;
}
