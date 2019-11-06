#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=2e5+5;
const int mod=1e9+7;
int n,pw2[N];

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
	int cnt,fir[N],dep[N],xdep[N],son[N],dfn[N],idx[N];
	int cdep[N],dp[N][3],top[N];
	struct edge{
		int to,nx;
	}eg[N];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void upd(const int x,const int f){
		if(top[x]==f) return;
		top[x]=f;
		dp[x][0]=(dp[x][0]+dp[x][2])%mod;
		dp[x][2]=0;
	}

	void dfs_dep(const int x){
		++cdep[dep[x]];
		xdep[x]=dep[x];
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			dep[y]=dep[x]+1;
			dfs_dep(y);
			if(xdep[x]<xdep[y]){
				son[x]=y;
				xdep[x]=xdep[y];
			}
		}
	}

	void dfs_ans(const int x){
		static int cnd;
		dfn[x]=++cnd;
		idx[cnd]=x;
		dp[x][0]=dp[x][1]=1;
		if(son[x]){
			dfs_ans(son[x]);
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==son[x]) continue;
			dfs_ans(y);
			for(int i=0; i<=xdep[y]-dep[y]; ++i){
				int tx=idx[dfn[x]+1+i],ty=idx[dfn[y]+i];
				upd(tx,x);
				int x0=dp[tx][0],x1=dp[tx][1],x2=dp[tx][2];
				int y0=(dp[ty][0]+dp[ty][2])%mod,y1=dp[ty][1];
				dp[tx][0]=(lint)x0*y0%mod;
				dp[tx][1]=((lint)x0*y1+(lint)x1*y0)%mod;
				dp[tx][2]=((lint)x1*y1+(lint)x2*(y0+y1))%mod;
			}
		}
	}

	int get_ans(){
		int ans=0;
		for(int x=0; ; x=son[x]){
			ans=(ans+(lint)dp[x][1]*pw2[n+1-cdep[dep[x]]])%mod;
			if(!son[x]) break;
		}
		return ans;
	}
}

int main(){
	n=nxi();
	pw2[0]=1;
	for(int i=1; i<=n; ++i){
		pw2[i]=(pw2[i-1]<<1)%mod;
	}
	for(int i=1; i<=n; ++i){
		G::add(nxi(),i);
	}
	G::dfs_dep(0);
	G::dfs_ans(0);
	printf("%d\n",G::get_ans());
	return 0;
}
