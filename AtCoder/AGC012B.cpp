#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
int n,m;
struct data{
	int c,t;
	friend bool operator < (const data &a,const data &b){
		return a.t<b.t;
	}
}dp[N][11];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=y<x?x:y;}
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
	int cnt,fir[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void solve(){
		for(int d=10; d; --d){
			for(int i=1; i<=n; ++i){
				for(int j=fir[i]; j; j=eg[j].nx){
					const int y=eg[j].to;
					apx(dp[y][d-1],dp[i][d]);
				}
			}
		}
	}
}

int main(){
#ifdef LOCAL
	freopen("paint.in","r",stdin);
	freopen("paint.out","w",stdout);
#endif
	n=nxi(),m=nxi();
	for(int i=1; i<=m; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	for(int q=nxi(),i=1; i<=q; ++i){
		const int x=nxi(),d=nxi(),c=nxi();
		apx(dp[x][d],(data){c,i});
	}
	G::solve();
	for(int i=1; i<=n; ++i){
		data res=(data){0,0};
		for(int j=0; j<=10; ++j){
			apx(res,dp[i][j]);
		}
		printf("%d\n",res.c);
	}
	return 0;
}
