#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;
const int N=2e5+5;
const int mod=998244353;
int n,ans;

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
	int cnt,cnd,fir[N],fa[N],dp[N],abuk[N][3];
	int dep[N],xdep[N],son[N],dfn[N],idx[N],tag[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}
	inline void init(){
		cnt=cnd=0;
		memset(fir+1,0,n*sizeof(int));
		memset(son+1,0,n*sizeof(int));
		for(int i=1; i<=n; ++i) tag[i]=1;
	}
	inline void psh(const int x){
		if(tag[x]!=1){
			dp[x]=(lint)dp[x]*tag[x]%mod;
			if(xdep[x]!=dep[x]){
				tag[idx[dfn[x]+1]]=(lint)tag[idx[dfn[x]+1]]*tag[x]%mod;
			}
			tag[x]=1;
		}
	}

	void dfs_dep(const int x){
		xdep[x]=dep[x];
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa[x]) continue;
			dep[y]=dep[x]+1;
			fa[y]=x;
			dfs_dep(y);
			if(xdep[y]>xdep[son[x]]) son[x]=y;
			apx(xdep[x],xdep[y]);
		}
	}

	void dfs_ans(const int x){
		static int pv1[N],pv2[N];
		dp[x]=1;
		dfn[x]=++cnd;
		idx[cnd]=x;
		if(son[x]) dfs_ans(son[x]);
		if(x==1){
			memset(abuk+1,0,xdep[1]*sizeof(abuk[0]));
			for(int s=1,i=1; i<=xdep[x]; ++i){
				int p=idx[dfn[x]+i];
				psh(p);
				abuk[i][0]=s;
				abuk[i][1]=dp[p];
				s=(s+dp[p])%mod;
				eprintf("%d: %d %d %d\n",i,abuk[i][0],abuk[i][1],abuk[i][2]);
			}
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(fa[x]==y||son[x]==y) continue;
			dfs_ans(y);
			pv1[0]=pv2[0]=1;
			const int depy=xdep[y]-dep[x];
			for(int j=1; j<=depy; ++j){//最长深度为d的方案数
				int a1=idx[dfn[x]+j],a2=idx[dfn[y]+j-1];
				psh(a1),psh(a2);
				pv1[j]=(pv1[j-1]+dp[a1])%mod;
				pv2[j]=(pv2[j-1]+dp[a2])%mod;
				if(x==1){
					abuk[j][2]=((lint)abuk[j][2]*pv2[j]+(lint)abuk[j][1]*dp[a2])%mod;
					abuk[j][1]=((lint)abuk[j][1]*pv2[j-1]+(lint)abuk[j][0]*dp[a2])%mod;
					abuk[j][0]=(lint)abuk[j][0]*pv2[j-1]%mod;
				}
				dp[a1]=((lint)pv1[j]*pv2[j]-(lint)pv1[j-1]*pv2[j-1])%mod;
			}
			if(xdep[y]<xdep[x]){
				int p=idx[dfn[x]+depy+1];
				tag[p]=(lint)tag[p]*pv2[xdep[y]-dep[x]]%mod;
			}
			eprintf("---\n");
			for(int i=1; i<=xdep[x]; ++i){
				eprintf("%d: %d %d %d\n",i,abuk[i][0],abuk[i][1],abuk[i][2]);
			}
		}
		if(x==1){
			for(int i=1; i<=xdep[1]; ++i){
				if(tag[idx[i+1]]!=1){
					abuk[i][2]=((lint)abuk[i][2]*tag[i+1])%mod;
					tag[i+2]=(lint)tag[i+2]*tag[i+1]%mod;
				}
			}
		}
	}
}

int main(){
	for(int T=nxi(); T; --T){
		n=nxi(),ans=0;
		G::init();
		for(int i=1; i<n; ++i){
			const int a=nxi(),b=nxi();
			G::add(a,b),G::add(b,a);
		}
		G::dfs_dep(1);
		G::dfs_ans(1);
		int ans=1;
		for(int i=1; i<=G::xdep[1]; ++i){
			ans=(ans+G::abuk[i][2])%mod;
		}
		printf("%d\n",ans);
	}
	return 0;
}
