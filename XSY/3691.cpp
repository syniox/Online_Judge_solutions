#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=405;
int n,val[N];
lint f[N][N],g[N][N];
//f: 向内j个点 g: 向外走j步 

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

namespace G{
	int cnt,sz[N],fir[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs(const int x,const int f){
		static lint tf[N];//x向下含自己到i个点
		sz[x]=1;
		for(int y,i=fir[x]; i; i=eg[i].nx){
			if((y=eg[i].to)!=f)
				dfs(y,x),sz[x]+=sz[y];
		}
		for(int i=1; i<=n; ++i){//内定x能到(含自己)i个点
			memset(tf,-10,(i+1)*sizeof(tf[0]));
			int s=1;
			tf[1]=(lint)val[x]*i;
			for(int j=fir[x]; j; j=eg[j].nx){
				const int y=eg[j].to;
				if(y==f) continue;
				for(int k=std::min(i,s); k; --k){
					for(int l=std::min(sz[y],i-k); l; --l)
						apx(tf[k+l],tf[k]+::f[y][l]);
					tf[k]+=g[y][i];
				}
				s+=sz[y];
			}
			::f[x][i]=tf[i];
			for(int j=1; j<=i; ++j)
				apx(g[x][i-j],tf[j]);
		}
	}
}

int main(){
	memset(f,-10,sizeof(f));
	memset(g,-10,sizeof(g));
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=2; i<=n; ++i){
		const int f=nxi();
		G::add(f,i),G::add(i,f);
	}
	G::dfs(1,0);
	printf("%lld\n",g[1][0]);
	return 0;
}
