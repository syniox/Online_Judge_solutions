#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;
const int N=5e4+5;
const int mod=998244353;
int n,m,dp[N][200][2];//dp[i][j][0/1] i子树 最大匹配j i是否必须匹配的方案数

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

	void dfs(const int x,const int fa){
		static int tmp[405][2];
		dp[x][0][0]=1;
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa) continue;
			dfs(y,x);
			const int lim_i=min(m,sz[x]/2+1);
			const int lim_j=min(m,sz[y]/2+1);
			memset(tmp,0,(lim_i+lim_j)*sizeof(tmp[0]));
			for(int i=0; i<lim_i; ++i){
				for(int j=0; j<lim_j; ++j){
					int y0=dp[y][j][0],y1=dp[y][j][1];
					tmp[i+j+1][1]=(tmp[i+j+1][1]+(lint)dp[x][i][0]*y0)%mod;
					tmp[i+j][0]=(tmp[i+j][0]+(lint)dp[x][i][0]*(y0+y1*2ll))%mod;
					tmp[i+j][1]=(tmp[i+j][1]+(lint)dp[x][i][1]*(y0+y1)*2ll)%mod;
				}
			}
			memset(dp[x],0,lim_i*sizeof(dp[x][0]));
			for(int i=0; i<lim_i+lim_j; ++i){
				int p=i%m;
				dp[x][p][0]=(dp[x][p][0]+tmp[i][0])%mod;
				dp[x][p][1]=(dp[x][p][1]+tmp[i][1])%mod;
			}
			sz[x]+=sz[y];
		}
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b),G::add(b,a);
	}
	G::dfs(1,1);
	printf("%d\n",(dp[1][0][0]+dp[1][0][1])%mod);
	return 0;
}
