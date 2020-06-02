#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
typedef long long lint;
const int N=1e5+5;
const int S=330;
int n,q,tot,val[N],bel[N],wgt[N][S];
lint tsum[S];

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
	int rt,cnt,fir[N],sz[N],dfn[N];
	lint sum[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs(const int x){
		static int cnd,buk[S];
		++buk[bel[x]];
		memcpy(wgt[x],buk,sizeof(buk));
		sz[x]=1;
		dfn[x]=++cnd;
		sum[x]=val[x];
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(sz[y]) continue;
			dfs(y);
			sum[x]+=sum[y];
			sz[x]+=sz[y];
		}
		--buk[bel[x]];
		tsum[bel[x]]+=sum[x];
	}
}

namespace B{
	lint bsum[S],tps[N],tags[S];
	lint qsum(const int x){
		return x?bsum[bel[x]-1]+tps[x]:0;
	}
	void build(){
		for(int i=1; i<=n; ++i){
			bsum[bel[G::dfn[i]]]+=val[i];
			tps[G::dfn[i]]=val[i];
		}
		for(int i=1; i<=n; ++i){
			tps[i]=tps[i-1]+tps[i];
		}
		for(int i=1; i<=n; ++i){
			tps[i]-=bsum[bel[i]-1];
		}
	}
	void add(int x,const int dlt){
		for(int i=x; bel[i]==bel[x]; ++i){
			tps[i]+=dlt;
		}
		for(int i=bel[x]; i<=tot; ++i){
			bsum[i]+=dlt;
		}
	}
}

inline lint qsum(const int x){
	return B::qsum(G::dfn[x]+G::sz[x]-1)-B::qsum(G::dfn[x]-1);
}

lint getans(const int a,const int b){
	lint ans=0;
	if(bel[a]==bel[b]){
		for(int i=a; i<=b; ++i)
			ans+=qsum(i);
	}
	else{
		for(int i=a; bel[i]==bel[a]; ++i)
			ans+=qsum(i);
		for(int i=b; bel[i]==bel[b]; --i)
			ans+=qsum(i);
		for(int i=bel[a]+1; i<bel[b]; ++i)
			ans+=tsum[i];
	}
	return ans;
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1,bsize=sqrt(n)+1; i<=n; ++i){
		val[i]=nxi();
		bel[i]=(i-1)/bsize+1;
	}
	tot=bel[n];
	for(int i=1; i<=n; ++i){
		const int a=nxi(),b=nxi();
		if(!a||!b) G::rt=a+b;
		else G::add(a,b),G::add(b,a);
	}
	G::dfs(G::rt);
	B::build();
	for(int i=1; i<=q; ++i){
		const int op=nxi(),a=nxi(),b=nxi();
		if(op==1){
			const int dlt=b-val[a];
			val[a]=b;
			for(int i=1; i<=tot; ++i){
				tsum[i]+=(lint)dlt*wgt[a][i];
			}
			B::add(G::dfn[a],dlt);
		}
		if(op==2){
			printf("%lld\n",getans(a,b));
		}
	}
	return 0;
}
