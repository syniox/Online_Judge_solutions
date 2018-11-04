#include <iostream>
#include <cstdio>
#include <cstring>
const int N=2005;
int n,q,hx[N][6];

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline bool jdg(const int x,const int y){
	for(int i=1;i<=q;++i){
		if(hx[x][i]>hx[y][i]) return 1;
	}
	return 0;
}

namespace G{
	int cnt,cnf,cnd,top,limit,dfn[N],ind[N],fir[N],sz[N],bel[N];
	bool vis[N];
	struct edge{
		int to,nx;
	}eg[N*N<<1];

	inline void init(){
		cnf=cnd=0;
		memset(ind,0,sizeof(ind));
		memset(dfn,0,sizeof(dfn));
		memset(sz,0,sizeof(sz));
		memset(vis,0,sizeof(vis));
	}

	inline void add(const int a,const int b){ 
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void tarjan(const int x){
		static int low[N],stk[N];
		stk[++top]=x;
		dfn[x]=low[x]=++cnd;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(y>limit) continue;
			if(dfn[y]){
				if(!vis[y]) apn(low[x],dfn[y]);
			}
			else{
				tarjan(y);
				apn(low[x],low[y]);
			}
		}
		if(low[x]==dfn[x]){
			++cnf;
			for(int j=0;j!=x;){
				j=stk[top--];
				vis[j]=1;
				++sz[cnf];
				bel[j]=cnf;
			}
		}
	}

	inline int solve(int limit){
		G::limit=limit;
		init();
		for(int i=1;i<=limit;++i){
			if(!vis[i]) tarjan(i);
		}
		for(int i=1;i<=limit;++i){
			for(int j=fir[i];j;j=eg[j].nx){
				const int y=eg[j].to;
				if(y<=limit&&bel[i]!=bel[y]) ++ind[bel[y]];
			}
		}
//		for(int i=1;i<=limit;++i){
//			printf("%d ",bel[i]);
//		}
//		puts("");
		for(int i=1;i<=cnf;++i){
			if(!ind[i]) return sz[i];
		}
		return 0;
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("c.in","r",stdin);
#endif
	n=nxi(),q=nxi();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=q;++j){
			hx[i][j]=nxi();
		}
	}
	if(q==1){
		for(int i=1;i<=n;++i) printf("1 ");
		return 0;
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(jdg(i,j)) G::add(i,j);
		}
	}
	for(int i=1;i<=n;++i){
		printf("%d ",G::solve(i));
	}
	puts("");
	return 0;
}
