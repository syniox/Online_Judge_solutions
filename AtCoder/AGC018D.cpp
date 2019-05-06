#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
int n;

inline int nxi(FILE *fd=stdin){
	int x=0;
	char c;
	while((c=fgetc(fd))>'9'||c<'0');
	while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
	return x;
}

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

namespace G{
	int cnt,split_v,fir[N],sz[N],xsz[N];
	lint tot;
	struct edge{
		int to,wi,nx;
	}eg[N<<1];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	void dfs_sz(const int x){
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!sz[y]){
				dfs_sz(y);
				sz[x]+=sz[y];
				apx(xsz[x],sz[y]);
			}
		}
	}

	int get_ndis(){
		int ndis=1e9;
		for(int x=1; x<=n; ++x){
			if(sz[x]<<1<n||xsz[x]<<1>n) continue;
			for(int i=fir[x]; i; i=eg[i].nx){
				apn(ndis,eg[i].wi);
			}
		}
		return ndis;
	}

	bool split(){
		for(int i=1; i<=n; ++i){
			if(sz[i]*2==n) return 1;
		}
		return 0;
	}

	void get_tot(){
		tot=0;
		for(int i=1; i<=n; ++i){
			for(int j=fir[i]; j; j=eg[j].nx){
				int tx=i,ty=eg[j].to;
				if(sz[tx]<sz[ty]) continue;
				int v1=sz[ty],v2=n-sz[ty];
				if(v1>v2) std::swap(v1,v2);
				int wgt=std::min(2*v1,2*v2-1);
				tot+=(lint)wgt*eg[j].wi;
			}
		}
	}
}

int main(){
	n=nxi();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi(),v=nxi();
		G::add(a,b,v);
		G::add(b,a,v);
	}
	G::dfs_sz(1);
	G::get_tot();
	if(G::split()){
		printf("%lld\n",G::tot);
		return 0;
	}
	printf("%lld\n",G::tot-G::get_ndis());
	return 0;
}
