#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N=1e5+5;
int n,val[N],idx[N],dp[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

class _Graph{
	public:
		int m,cnt,fir[N];
		struct edge{
			int to,wi,nx;
		}eg[N<<1];

		inline void clear(){
			memset(fir,0,sizeof(fir));
			cnt=m=0;
		}

		inline void add(const int a,const int b,v){
			eg[++cnt]=(edge){b,v,fir[a]};
			fir[a]=cnt;
		}
};

class _Tree:public _Graph{
	protected:
		int cnd,sz[N],dep[N],fa[N],top[N],son[N];
	public:
		int dfn[N];

		void dfs_son(const int x){
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(!sz[y]){
					fa[y]=x;
					dep[y]=dep[x]+1;
					dfs_son(y);
					if(sz[y]>sz[son[x]]) son[x]=y;
					sz[x]+=sz[y];
				}
			}
		}

		void dfs_top(const int x){
			top[x]=son[fa[x]]==x?top[fa[x]]:x;
			dfn[x]=++cnd;
			if(son[x]) dfs_top(son[x]);
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(!top[y]) dfs_top(y);
			}
		}

		inline int get_lca(int x,int y){
			while(top[x]!=top[y]){
				if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
				else y=fa[top[y]];
			}
			return dep[x]<dep[y]?x:y;
		}
}T;

class _VirTr: public _Graph{
	protected:
}V;

int main(){
	static int seq[N];
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		idx[val[i]]=i;
	}
	for(int i=1; i<=n; ++i){
		const int a=nxi(),b=nxi();
		T.add(a,b,1);
		T.add(b,a,1);
	}
	T.dfs_son(1);
	T.dfs_top(1);
	for(int i=1; i<=n; ++i){
		int pt=0;
		for(int j=i; j<=n; j+=i){
			seq[pt++]=idx[j];
		}
		V.claar();
		V.build(seq,pt);
		dp[i]=V.solve();
	}
	return 0;
}
