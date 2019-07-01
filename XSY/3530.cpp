#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <sys/mman.h>
#include <unistd.h>
typedef long long lint;
const int N=1e6+5;
const int mod=1e9+7;
int n,q,l,val[N],nxt_v[N];

namespace IO{
	char *ibuf;
	struct _Init{
		_Init(){ibuf=(char*)mmap(0,lseek(0,0,SEEK_END),PROT_READ,MAP_PRIVATE,0,0);}
	}_init;
	inline int nxi(){
		int x=0;
		char c;
		while((c=*ibuf++)>'9'||c<'0');
		while(x=x*10-48+c,(c=*ibuf++)>='0'&&c<='9');
		return x;
	}
}
using IO::nxi;

namespace G{
	int cnt,fir[N],fa[N],f[N][2],g[N][2];
	int ans,st_f[N],st_g[N];
	struct edge{
		int to,nx;
	}eg[N];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs_ans(const int x){
		int res=st_f[val[x]-1];
		if(val[x]==l) ans=(ans+res)%mod;
		st_f[val[x]]=(st_f[val[x]]+res)%mod;
		for(int i=fir[x]; i; i=eg[i].nx){
			dfs_ans(eg[i].to);
		}
		st_f[val[x]]=(st_f[val[x]]-res+mod)%mod;
	}

	void init(){
		ans=0;
		st_f[0]=1;
		dfs_ans(1);
		ans%=mod;
	}

	void dfs(const int x){
		int lst_0=st_g[val[x]+1],lst_1=st_g[nxt_v[x]+1];
		f[x][0]=st_f[val[x]-1];
		f[x][1]=st_f[nxt_v[x]-1];
		st_f[nxt_v[x]]=(st_f[nxt_v[x]]+f[x][1])%mod;
		for(int i=fir[x]; i; i=eg[i].nx){
			dfs(eg[i].to);
		}
		g[x][0]=val[x]==l?1:(st_g[val[x]+1]-lst_0+mod)%mod;
		g[x][1]=nxt_v[x]==l?1:(st_g[nxt_v[x]+1]-lst_1+mod)%mod;
		st_f[nxt_v[x]]=(st_f[nxt_v[x]]-f[x][1]+mod)%mod;
		st_g[val[x]]=(st_g[val[x]]+g[x][0])%mod;
	}

	int calc(const int st,const int lim){
		int res=0;
		for(int i=1; i<=lim; ++i){
			ans=(ans-(lint)f[i][0]*g[i][0]+(lint)f[i][1]*g[i][1])%mod;
			ans=(ans+mod)%mod;
			res=(res+(lint)ans*(st+i))%mod;
		}
		return res;
	}
}

int main(){
	n=nxi(),q=nxi(),l=nxi();
	for(int i=2; i<=n; ++i){
		G::fa[i]=nxi();
		G::add(G::fa[i],i);
	}
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	G::init();
	lint ans=0;
	for(int i=1; i<=(q+n-1)/n; ++i){
		const int lim=std::min(n,q-(i-1)*n);
		for(int j=1; j<=lim; ++j){
			nxt_v[j]=nxi();
		}
		for(int j=lim+1; j<=n; ++j){
			nxt_v[j]=val[j];
		}
		G::dfs(1);
		ans+=G::calc((i-1)*n,lim);
		memcpy(val+1,nxt_v+1,n*sizeof(val[0]));
	}
	printf("%lld\n",ans%mod);
	return 0;
}
