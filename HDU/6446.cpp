#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;
using lint=long long;

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<=y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>=y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
	static struct{
		template <class T> operator T(){
			T x=0;
			char c;
			while(((c=getchar())>'9'||c<'0')&&c!='-');
			const bool f=c=='-'&&(c=getchar());
			while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
			return f?-x:x;
		}
	}ni;
}
using namespace utils;
const int N=1e5+5;
const int mod=1e9+7;
int n,tot;

namespace G{
	int cnt,fir[N],sz[N],dis[N];
	struct edge{
		int to,wi,nx;
	}eg[N<<1];

	inline void reset(){
		cnt=1,tot=0;
		memset(fir+1,0,n*sizeof(int));
		memset(dis+1,0,n*sizeof(int));
	}
	inline void adde(const int a,const int b,const int v){
		eg[++cnt]={b,v,fir[a]};
		fir[a]=cnt;
	}
	void dfs(const int x,const int f){
		sz[x]=1,dis[x]=0;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==f) continue;
			dfs(y,x);
			int dy=((lint)sz[y]*eg[i].wi+dis[y])%mod;
			tot=(tot+(lint)dis[x]*sz[y]+(lint)sz[x]*dy)%mod;
			sz[x]+=sz[y];
			dis[x]=(dis[x]+dy)%mod;
		}
	}
}

int main(){
	while(cin>>n){
		G::reset();
		for(int i=1; i<n; ++i){
			int a=ni,b=ni,v=ni;
			G::adde(a,b,v);
			G::adde(b,a,v);
		}
		G::dfs(1,0);
		tot=(tot*2ll)%mod;
		for(int i=1; i<=n-1; ++i){
			tot=(lint)tot*i%mod;
		}
		printf("%d\n",tot);
	}
	return 0;
}
