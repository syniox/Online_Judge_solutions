#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long lint;
const int N=1e5+5;
const int S=640;
const int mod=998244353;
int n,val[N],finv[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
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

inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

namespace G{
	int cnt,fir[N],dgr[N],fa[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		fa[b]=a;
		++dgr[a];
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	int dfs(const int x,const int t){//t==1?
		static int cache[S][N];
		if(t<S&&cache[t][x]) return cache[t][x];
		int ans;
		if(t==1){
			ans=val[x]+1;
		}else{
			ans=(1-fpow(t,val[x]+1)+mod);
			ans=(lint)ans*finv[t]%mod;
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			ans=(lint)ans*dfs(eg[i].to,t)%mod;
		}
		if(t<S) cache[t][x]=ans;
		return ans;
	}
}

int main(){
	n=nxi();
	for(int i=2; i<=n; ++i){
		G::add(nxi(),i);
	}
	finv[0]=fpow(1,mod-2);
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		finv[i]=fpow(1-i+mod,mod-2);
	}
	for(int i=1; i<=n; ++i){
		printf("%d\n",G::dfs(i,G::dgr[i]));
	}
	return 0;
}
