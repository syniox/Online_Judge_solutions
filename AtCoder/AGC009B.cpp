#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N=1e5+5;
int n;

template <class T> inline void apx(T &x,const T y){
	x>y?0:x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,fir[N],dp[N];
	struct edge{
		int to,nx;
	}eg[N];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs(const int x){
		static int buk[N];
		for(int i=fir[x]; i; i=eg[i].nx){
			dfs(eg[i].to);
		}
		int pt=0;
		for(int i=fir[x]; i; i=eg[i].nx){
			buk[++pt]=dp[eg[i].to];
		}
		std::sort(buk+1,buk+pt+1);
		for(int i=pt; i; --i){
			apx(dp[x],buk[i]+pt-i+1);
		}
	}
}

int main(){
	n=nxi();
	for(int i=2; i<=n; ++i){
		G::add(nxi(),i);
	}
	G::dfs(1);
	printf("%d\n",G::dp[1]);
	return 0;
}
