#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N=1e5+5;
int n,m;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,fir[N],idx[N],val[N],dep[N];
	int tick,tag[N];
	class edge{
		public:
			int to,wi,nx;
	}eg[N<<1];

	inline void init(){
		for(int i=1; i<=n; ++i) idx[i]=i;
	}

	inline bool cmp_val(const int a,const int b){
		return val[a]<val[b];
	}

	inline void add_edge(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	inline void get_mtrx(){
		for(int i=1; i<=n; ++i){
			val[i]=nxi();
		}
		std::sort(idx+1,idx+n+1,cmp_val);
		for(int i=1; i<n; ++i){
			if(!val[idx[i]]) continue;
			add_edge(idx[i+1],idx[i],val[idx[i+1]]-val[idx[i]]);
		}
	}

	int dfs(const int x){
		int tmp=0;
		tag[x]=tick;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!tag[y]){
				dep[y]=dep[x]+eg[i].wi;
				if((tmp=dfs(y))) return tmp;
			}
			else if(tag[y]==tag[x]&&dep[y]!=dep[x]+eg[i].wi){
				return dep[x]-dep[y]+eg[i].wi;
			}
		}
		return 0;
	}
}

int main(){
	n=nxi(),m=nxi();
	G::init();
	for(int i=1; i<=m; ++i){
		G::get_mtrx();
	}
	for(int i=1; i<=n; ++i){
		if(G::tag[i]) continue;
		++G::tick;
		int tmp=G::dfs(i);
		if(tmp){
			printf("%d\n",tmp);
			return 0;
		}
	}
	puts("-1");
	return 0;
}
