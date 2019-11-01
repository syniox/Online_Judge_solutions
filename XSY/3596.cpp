#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=2e5+5;
int n,val[N];

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

struct pnt{
	int x;
	lint y;
	friend bool operator < (const pnt &a,const pnt &b){
		return a.x*b.y-a.y*b.x<0;
	}
};

namespace G{
	int cnt=1,fir[N],sz[N<<1];
	lint sum[N<<1],ans[N<<1],ans_p[N];
	pnt buk[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	int build(const int x,const int e){
		int top=0;
		sum[e]=ans[e]=val[x];
		sz[e]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			if(i==(e^1)) continue;
			buk[++top]=(pnt){sz[i],sum[i]};
			ans[e]+=ans[i];
			sz[e]+=sz[i];
			sum[e]+=sum[i];
		}
		std::sort(buk+1,buk+top+1);
		return top;
	}

	void dfs1(const int x,const int e){
		for(int i=fir[x]; i; i=eg[i].nx){
			if(i==(e^1)) continue;
			dfs1(eg[i].to,i);
		}
		int top=build(x,e);
		for(int dsz=1,i=1; i<=top; ++i){
			ans[e]+=dsz*buk[i].y;
			dsz+=buk[i].x;
		}
	}

	void dfs2(const int x,const int e){
		static int csz[N];
		static lint csum[N];
		int top=build(x,1);
		csz[0]=1,ans_p[x]=ans[1];
		for(int i=1; i<=top; ++i){
			ans_p[x]+=csz[i-1]*buk[i].y;
			csum[i]=csum[i-1]+buk[i].y;
			csz[i]=csz[i-1]+buk[i].x;
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			if(i==(e^1)) continue;
			int pos=std::lower_bound(buk+1,buk+top+1,(pnt){sz[i],sum[i]})-buk;
			sz[i^1]=csz[top]-sz[i];
			sum[i^1]=sum[1]-sum[i];
			ans[i^1]=ans_p[x]-ans[i]-sum[i]*csz[pos-1]-sz[i]*(csum[top]-csum[pos]);
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			if(i!=(e^1)) dfs2(eg[i].to,i);
		}
	}
}

int main(){
	n=nxi();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	G::dfs1(1,1);
	G::dfs2(1,1);
	lint ans=1e16;
	for(int i=1; i<=n; ++i){
		apn(ans,G::ans_p[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
