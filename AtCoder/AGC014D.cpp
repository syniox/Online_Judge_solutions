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

namespace G{
	int cnt,fir[N];
	bool linked[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs(const int x,const int fa){
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa) continue;
			dfs(y,x);
			if(!linked[y]){
				if(linked[x]) return;
				linked[x]=linked[y]=1;
			}
		}
	}

	bool link(){
		for(int i=1; i<=n; ++i){
			if(!linked[i]) return 0;
		}
		return 1;
	}
}

int main(){
	n=nxi();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	G::dfs(1,1);
	puts(G::link()?"Second":"First");
	return 0;
}
