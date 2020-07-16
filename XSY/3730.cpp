#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline lint nxi(){
		lint x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

const int N=1005;
const int mod=1e9+7;
int n,m;
lint q;
bool use[N<<1];
struct edge{
	int a,b,v;
	friend bool operator < (const edge &a,const edge &b){
		return a.v<b.v;
	}
}eg[N<<1];

namespace U{
	int fa[N];
	int qrt(const int x){
		return fa[x]?fa[x]=qrt(fa[x]):x;
	}
}

inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

lint kruskal(){
	lint ans=0;
	std::sort(eg+1,eg+m+1);
	for(int i=1; i<=m; ++i){
		const int a=U::qrt(eg[i].a),b=U::qrt(eg[i].b);
		if(a==b) continue;
		ans+=eg[i].v;
		use[i]=1;
		U::fa[a]=b;
	}
	return ans;
}

namespace G{
	const int G=12;
	int cnt,fir[N],dep[N],fa[N][G],dis[N][G];
	struct edge{
		int to,wi,nx;
	}eg[N<<1];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	void dfs(const int x){
		for(int i=1; fa[x][i-1]; ++i){
			fa[x][i]=fa[fa[x][i-1]][i-1];
			dis[x][i]=std::max(dis[x][i-1],dis[fa[x][i-1]][i-1]);
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa[x][0]) continue;
			dep[y]=dep[x]+1;
			fa[y][0]=x;
			dis[y][0]=eg[i].wi;
			dfs(y);
		}
	}

	int qmx(int x,int y){
		int ans=0;
		if(dep[x]<dep[y]) swap(x,y);
		for(int tmp=dep[x]-dep[y],i=0; i<G; ++i){
			if(tmp>>i&1){
				apx(ans,dis[x][i]);
				x=fa[x][i];
			}
		}
		if(x==y) return ans;
		for(int i=G-1; ~i; --i){
			if(fa[x][i]==fa[y][i]) continue;
			apx(ans,max(dis[x][i],dis[y][i]));
			x=fa[x][i],y=fa[y][i];
		}
		return max(ans,max(dis[x][0],dis[y][0]));
	}

	int solve(const int tgt){
		for(int i=1; i<=m; ++i){
			if(!use[i]) continue;
			add(::eg[i].a,::eg[i].b,::eg[i].v);
			add(::eg[i].b,::eg[i].a,::eg[i].v);
		}
		dfs(1);
		int just=0,after=0;
		for(int i=1; i<=m; ++i){
			if(use[i]) continue;
			int dlt=::eg[i].v-qmx(::eg[i].a,::eg[i].b);
			if(dlt==tgt) ++just;
			else if(dlt>tgt) ++after;
		}
		int ans=2ll*(fpow(2,just)-1ll)*fpow(2,after)%mod;
		if(tgt==0) ans=(ans+(fpow(2,n-1)-2ll+mod)*fpow(2,m-n+1))%mod;
		return ans;
	}
}

int main(){
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1; i<=m; ++i){
		eg[i]=(edge){(int)nxi(),(int)nxi(),(int)nxi()};
	}
	lint ans=kruskal();
	if(ans>q||q-ans>1e9) return puts("0"),0;
	printf("%d\n",G::solve(q-ans));
	return 0;
}
