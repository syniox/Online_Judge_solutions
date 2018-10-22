#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1e5+5;
int n,dep[N],len[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,fa[N],fir[N];
	struct edge{
		int to,nx;
	}eg[N<<1];
	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}
	void dfs(const int x){
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(fa[x]!=y){
				fa[y]=x;
				dfs(y);
				len[x]^=len[y]+1;
			}
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<n;++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	G::dfs(1);
	puts(len[1]?"Alice":"Bob");
	return 0;
}
