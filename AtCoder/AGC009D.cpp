#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=1e5+5;
int n;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int hbit(int x){
	int ans=0;
	for(int i=16; i; i>>=1){
		if(x>>i) x>>=i,ans+=i;
	}
	return ans;
}

namespace G{
	int cnt,ans,fir[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	inline int dfs(const int x,const int fa){
		int cand=0,cor=0;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa){
				int tmp=dfs(y,x);
				cand|=cor&tmp;
				cor|=tmp;
			}
		}
		int ans=-1;
		for(int i=0; i<30; ++i){
			if(!(cand>>i)&&!(cor>>i&1)){
				ans=i;
				break;
			}
		}
		int tmp=((1<<30)-1)^((1<<ans)-1);
		assert(~ans);
		return (cor&tmp)|1<<ans;
	}
}

int main(){
	n=nxi();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	printf("%d\n",hbit(G::dfs(1,0)));
	return 0;
}
