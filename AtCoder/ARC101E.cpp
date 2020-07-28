#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;
const int N=5005;
const int mod=1e9+7;
int n,wans[N],dp[N][N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

namespace G{
	int cnt,fir[N],sz[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs(const int x){
		dp[x][1]=sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(sz[y]) continue;
			dfs(y);
			int tot=sz[x]+sz[y];
			for(int j=tot; j; --j){
				int res=(mod-(lint)dp[x][j]*dp[y][0]%mod)%mod;
				for(int k=min(sz[y],j-1); k&&j-k<=sz[x]; --k){
					res=(res+(lint)dp[x][j-k]*dp[y][k])%mod;
				}
				dp[x][j]=res;
			}
			sz[x]+=sz[y];
		}
		assert(!dp[x][0]);
		for(int i=2; i<=sz[x]; i+=2){
			dp[x][0]=(dp[x][0]+(lint)dp[x][i]*wans[i])%mod;
		}
	}
}

int main(){
	n=nxi();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b),G::add(b,a);
	}
	wans[0]=1;
	for(int i=2; i<=n; i+=2){
		wans[i]=(lint)wans[i-2]*(i-1)%mod;
	}
	G::dfs(1);
	printf("%d\n",dp[1][0]);
	return 0;
}
