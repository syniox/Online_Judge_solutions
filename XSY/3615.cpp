#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
int n,m;

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
	int cnt=1,fir[N],dgr[N];
	bool vis[N*3],use[N*5];
	struct edge{
		int to,nx;
	}eg[N*5];

	inline void add(const int a,const int b){
		++dgr[a],++dgr[b];
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,fir[b]};
		fir[b]=cnt;
	}

	void dfs(const int x,const int d){
		static int cns;
		for(int &i=fir[x]; i; i=eg[i].nx){
			if(vis[i>>1]) continue;
			const int y=eg[i].to,tmp=i;
			vis[i>>1]=1;
			dfs(y,d^1);
			use[tmp^(++cns&1)]=1;
		}
	}

	void solve(){
		for(int lst=0,i=1; i<=n; ++i){
			if((dgr[i]&1)==0) continue;
			if(lst) add(i,lst),lst=0;
			else lst=i;
		}
		if((cnt-1)>>1&1) add(1,1);
		dfs(1,0);
		printf("%d\n",(cnt-1)>>1);
		for(int i=2; i<=cnt; ++i){
			if(use[i]){
				printf("%d %d\n",eg[i^1].to,eg[i].to);
			}
		}
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=m; ++i){
		G::add(nxi(),nxi());
	}
	G::solve();
	return 0;
}
