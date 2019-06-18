#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=17;
const int mod=1e9+7;
int n,m,tot,add_v[N][N],pf[1<<N],lg2[1<<N],dp[1<<N];
struct _pair{
	int x,y;
}lim[N];

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

template <class T,size_t S>
class _disc{
	public:
		T v[S],*tl;
		int tot;
		_disc(){tl=v;}
		inline void insert(const T &x){
			*++tl=x;
		}
		inline void build(){
			std::sort(v+1,tl+1);
			tl=std::unique(v+1,tl+1)-1;
			tot=tl-v;
		}
		inline int ask(const T &x){
			return std::lower_bound(v+1,tl+1,x)-v;
		}
};
_disc <int,N<<1> d_pt,d_vl;

namespace U{
	int fa[N<<1];
	inline void init(){
		for(int i=0; i<N<<1; ++i) fa[i]=i;
	}
	int find_rt(const int x){
		return fa[x]==x?x:fa[x]=find_rt(fa[x]);
	}
	inline void merge(int x,int y){
		x=find_rt(x),y=find_rt(y);
		if(x!=y) fa[x]=y;
	}
}

int main(){
	const int inv9=fpow(9,mod-2);
	U::init();
	n=nxi(),m=nxi();
	for(int i=1; i<=m; ++i){
		lim[i].x=nxi()-1,lim[i].y=nxi();
		d_pt.insert(lim[i].x);
		d_pt.insert(lim[i].y);
	}
	d_pt.insert(0);
	d_pt.build();
	for(int i=1; i<=m; ++i){
		lim[i].x=d_pt.ask(lim[i].x);
		lim[i].y=d_pt.ask(lim[i].y);
		U::merge(lim[i].x,lim[i].y);
	}
	for(int i=1; i<=d_pt.tot; ++i){
		d_vl.insert(U::find_rt(i));
	}
	d_vl.build();
	for(int i=1; i<=d_vl.tot; ++i){
		for(int j=1; j<=d_vl.tot; ++j){
			add_v[i][j]=1;
		}
	}
	for(int i=1; i<d_pt.tot; ++i){
		int p1=d_vl.ask(U::find_rt(i));
		int p2=d_vl.ask(U::find_rt(i+1));
		int dis=d_pt.v[i+1]-d_pt.v[i];
		if(p1>p2) std::swap(p1,p2);
		int wgt=(lint)(fpow(10,dis)+mod-1)*inv9%mod;
		wgt=(lint)(wgt+1)*fpow(wgt,mod-2)%mod;
		add_v[p1][p2]=(lint)add_v[p1][p2]*wgt%mod;
	}
	tot=d_vl.tot;
	for(int i=1; i<=tot; ++i){
		lg2[1<<i]=i;
	}
	pf[0]=1;
	for(int i=1; i<1<<tot; ++i){
		int lbit=lg2[i&-i];
		pf[i]=pf[i^(i&-i)];
		for(int j=lbit; j<tot; ++j){
			if(i>>j&1) pf[i]=(lint)pf[i]*add_v[lbit+1][j+1]%mod;
		}
	}
	assert(d_pt.v[1]==0);
	int pos1=d_vl.ask(U::find_rt(1));
	for(int i=0; i<1<<tot; ++i){
		if(i>>(pos1-1)&1) dp[i]=pf[i];
	}
	for(int t=1; t<9; ++t){
		for(int i=(1<<tot)-1; ~i; --i){
			if((i>>(pos1-1)&1)==0) continue;
			for(int j=i; j; j=(j-1)&i){
				dp[i]=(dp[i]+(lint)pf[j]*dp[i^j])%mod;
			}
		}
	}
	int ans=1;
	for(int i=1; i<d_pt.tot; ++i){
		ans=(lint)ans*(fpow(10,d_pt.v[i+1]-d_pt.v[i])+mod-1)%mod*inv9%mod;
	}
	ans=(lint)ans*fpow(10,n-d_pt.v[d_pt.tot])%mod;
	printf("%lld\n",(lint)ans*dp[(1<<tot)-1]%mod);
	return 0;
}
