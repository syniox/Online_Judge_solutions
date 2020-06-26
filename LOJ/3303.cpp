#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=5.25e5+15;
int n,val[N];
lint ans;

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

namespace G{
	int cnt,fir[N],dep[N];
	bool *buk[21];
	struct edge{
		int to,nx;
	}eg[N<<1];

	void init(){
		for(int i=0; i<21; ++i)
			buk[i]=new bool[1<<(i+1)];
	}
	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	int dfs(const int x){
		int res=0;
		for(int i=0; i<21; ++i){
			const int all=(1<<(i+1))-1;
			res|=buk[i][dep[x]&all]<<i;
			int v=val[x]&all,p1=(v+dep[x]+(1<<i))&all,p2=(v+dep[x])&all;
			if(v!=(1<<i)&&(v>>i&1||v==0))
				res^=1<<i;
			buk[i][p1]^=1,buk[i][p2]^=1;
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			dep[eg[i].to]=dep[x]+1;
			res^=dfs(eg[i].to);
		}
		for(int i=0; i<21; ++i){
			res^=buk[i][dep[x]&((1<<(i+1))-1)]<<i;
		}
		ans+=res;
		//eprintf("%d: %d\n",x,res);
		return res;
	}
}

int main(){
	G::init();
	n=nxi();
	for(int i=1; i<=n; ++i)
		val[i]=nxi();
	for(int i=2; i<=n; ++i)
		G::add(nxi(),i);
	G::dfs(1);
	printf("%lld\n",ans);
	return 0;
}
