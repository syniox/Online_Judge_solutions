#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=1e5+5;
const int mod=998244353;
int n,ans,val[N],mean[N],no_up[N];

template <class T> inline void twk(T &x){
	if(x<0) x+=mod;
	else if(x>=mod) x-=mod;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int qpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

namespace G{
	int cnt,fir[N],dgr[N],invdgr[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
		++dgr[b];
	}

	inline void build_inv(){
		for(int i=1; i<=n; ++i){
			invdgr[i]=dgr[i]==1?1:qpow(dgr[i],mod-2);
		}
	}

	inline void dfs_up(const int x,const int fa){
		if(dgr[x]==1){
			no_up[x]=1;
			return;
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa){
				dfs_up(y,x);
				twk(no_up[x]+=no_up[y]);
			}
		}
		no_up[x]=(lint)no_up[x]*qpow(no_up[x]+1,mod-2)%mod;
	}

	inline void dfs_mean(const int x,const int fa){
		int res_up,res_dn=0;
		if(x==1) res_up=1;
		else res_up=(lint)mean[fa]*invdgr[fa]%mod;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa) twk(res_dn+=1-no_up[y]);
		}
		twk(res_dn=1-(lint)res_dn*invdgr[x]%mod);
		mean[x]=(lint)res_up*qpow(res_dn,mod-2)%mod;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa) dfs_mean(y,x);
		}
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=1; i<n; ++i){
		const int x=nxi(),y=nxi();
		G::add(x,y);
		G::add(y,x);
	}
	G::dfs_up(1,1);
	G::build_inv();
	G::dfs_mean(1,1);
	for(int i=1; i<=n; ++i){
		ans=(ans+(lint)mean[i]*val[i])%mod;
	}
	printf("%d\n",ans);
	for(int q=nxi(); q; --q){
		int x=nxi(),v=nxi(),delta=v-val[x];
		val[x]=v;
		twk(ans=(ans+(lint)delta*mean[x])%mod);
		printf("%d\n",ans);
	}
	return 0;
}
