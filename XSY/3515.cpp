#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e5+5;
int n,m,dgr[N],id[N],rnk[N],ans[N],edg[N][2];

namespace utils{
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
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

inline bool cmp_dgr(const int a,const int b){
	return dgr[a]>dgr[b];
}

namespace G{
	//f: 简单路径数 c: 环数
	int fir[N],d[N],c3[N];
	lint f2[N],f3[N],f4[N],c4[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		static int cnt;
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,fir[b]};
		fir[b]=cnt;
	}

	void get_c(){
		static int tmp[N];
		//c3
		for(int x=1; x<=n; ++x){
			for(int i=fir[x]; i; i=eg[i].nx){
				if(eg[i].to>x) tmp[eg[i].to]=x;
			}
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(y<x) continue;
				for(int j=fir[y]; j; j=eg[j].nx){
					const int z=eg[j].to;
					if(z>y&&tmp[z]==x){
						++c3[x],++c3[y],++c3[z];
					}
				}
			}
		}
		//c4
		memset(tmp+1,0,n*sizeof(tmp[0]));
		for(int x=1; x<=n; ++x){
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(y<x) continue;
				for(int j=fir[y]; j; j=eg[j].nx){
					if(eg[j].to>x) ++tmp[eg[j].to];
				}
			}
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(y<x) continue;
				for(int j=fir[y]; j; j=eg[j].nx){
					const int z=eg[j].to;
					if(z>x) c4[y]+=tmp[z]-1;
				}
			}
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				for(int j=fir[y]; j; j=eg[j].nx){
					const int z=eg[j].to;
					if(!tmp[z]) continue;
					lint res=(lint)tmp[z]*(tmp[z]-1)>>1;
					c4[x]+=res;
					c4[z]+=res;
					tmp[z]=0;
				}
			}
		}
	}

	void get_f(){
		for(int i=1; i<=n; ++i){
			d[i]=::dgr[id[i]];
		}
		//f2
		for(int x=1; x<=n; ++x){
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				f2[x]+=d[y]-1;
			}
		}
		//f3
		for(int x=1; x<=n; ++x){
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				f3[x]+=f2[y]-(d[x]-1);
			}
			f3[x]-=c3[x]*2;
		}
		//f4
		for(int x=1; x<=n; ++x){
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				f4[x]+=f3[y]-(f2[x]-(d[y]-1));
			}
			f4[x]-=c4[x]*2;
			f4[x]+=c3[x]*2;
			f4[x]-=c3[x]*2*(d[x]-2);
		}
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=m; ++i){
		edg[i][0]=nxi();
		edg[i][1]=nxi();
		++dgr[edg[i][0]];
		++dgr[edg[i][1]];
	}
	for(int i=1; i<=n; ++i){
		id[i]=i;
	}
	std::sort(id+1,id+n+1,cmp_dgr);
	for(int i=1; i<=n; ++i){
		rnk[id[i]]=i;
	}
	for(int i=1; i<=m; ++i){
		G::add(rnk[edg[i][0]],rnk[edg[i][1]]);
	}
	G::get_c();
	G::get_f();
	for(int i=1; i<=n; ++i){
		printf("%lld\n",G::f4[rnk[i]]);
	}
	return 0;
}
