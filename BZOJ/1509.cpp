#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=2e5+5;
int n;

template <class T> inline void xswp(T &x,T &y){
	if(x<y) std::swap(x,y);
}

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,fir[N],dis_fa[N];
	lint ans,xlen1[N],xlen2[N],xlen3[N];
	struct edge{
		int to,wi,nx;
	}eg[N<<1];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	void dfs_len(const int x,const int fa){
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa) continue;
			dis_fa[y]=eg[i].wi;
			dfs_len(y,x);
			lint tmp=xlen1[y]+eg[i].wi;
			xswp(xlen1[x],tmp);
			xswp(xlen2[x],tmp);
			xswp(xlen3[x],tmp);
		}
	}

	void dfs_ans(const int x,const int fa){
		if(fa){
			lint tmp=dis_fa[x]+(xlen1[x]+dis_fa[x]==xlen1[fa]?xlen2[fa]:xlen1[fa]);
			xswp(xlen1[x],tmp);
			xswp(xlen2[x],tmp);
			xswp(xlen3[x],tmp);
		}
		lint v=xlen1[x]+(xlen2[x]<<1)+xlen3[x];
		apx(ans,xlen1[x]+(xlen2[x]<<1)+xlen3[x]);
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa) dfs_ans(y,x);
		}
	}
}

int main(){
	n=nxi(),nxi();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi(),v=nxi();
		G::add(a,b,v);
		G::add(b,a,v);
	}
	G::dfs_len(1,0);
	G::dfs_ans(1,0);
	printf("%lld\n",G::ans);
	return 0;
}
