#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
typedef long long lint;
const int N=1e5+5;
const int mod=1e9+7;
int n;

namespace utils{
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

template <class T>
inline int fpow(int x,T t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

namespace G{
	int rt,ans,cnt,fir[N<<1];
	int cir_dep,dep[N<<1];
	int eg_cnt,nd_cnt;
	bool vis[N<<1];
	std::vector <int> cir_l;
	struct edge{
		int to,nx;
	}eg[N<<2];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	bool dfs_cir(const int x,const int fa){
		++nd_cnt;
		vis[x]=1;
		bool on_cir=0;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			++eg_cnt;
			if(y==fa) continue;
			if(vis[y]){
				if(~cir_dep) continue;
				cir_dep=dep[y];
				on_cir=1;
			}
			else{
				dep[y]=dep[x]+1;
				on_cir|=dfs_cir(y,x);
			}
		}
		on_cir&=dep[x]>=cir_dep;
		if(on_cir) cir_l.push_back(x);
		return on_cir;
	}

	int dfs_tot(const int x,const int fa){
		int sz=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==rt&&y!=fa) assert(y>fa);
			if(y==fa||y==rt) continue;
			if(y<fa) sz+=dfs_tot(y,x);
			else dfs_tot(y,x);
		}
		ans=(lint)ans*sz%mod;
		return sz;
	}

	int solve(const int x){
		cir_l.clear();
		eg_cnt=nd_cnt=0;
		cir_dep=-1;
		dfs_cir(x,0);
		if(eg_cnt!=nd_cnt<<1) return 0;
		const int sz=cir_l.size();
		assert(sz);
		int r=0,res=0;
		for(int i=1; i<(int)cir_l.size(); ++i){
			if(cir_l[i]<cir_l[r]) r=i;
		}
		{
			int f,x;
			if((f=r-1)<0) f=sz-1;
			if((x=f-1)<0) x=sz-1;
			ans=1;
			G::rt=cir_l[x];
			dfs_tot(cir_l[x],cir_l[f]);
			res=(res+fpow(ans,mod-2))%mod;
		}
		{
			int f,x;
			if((f=r+1)==sz) f=0;
			if((x=f+1)==sz) x=0;
			ans=1;
			G::rt=cir_l[x];
			dfs_tot(cir_l[x],cir_l[f]);
			res=(res+fpow(ans,mod-2))%mod;
		}
		return res;
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n<<1; ++i){
		int x=nxi(),y=nxi();
		G::add(x,y+n);
		G::add(y+n,x);
	}
	int res=1;
	for(int i=1; res&&i<=n; ++i){
		if(!G::vis[i]) res=(lint)res*G::solve(i)%mod;
	}
	for(int i=1; i<=n<<1; ++i){
		res=(lint)res*i%mod;
	}
	printf("%d\n",res);
	return 0;
}
