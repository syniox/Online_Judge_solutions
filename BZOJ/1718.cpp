#include <iostream>
#include <cstdio>
#include <cstring>
const int N=5005;
int n,m;

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

namespace G{
	int cnt,cnf,ans,fa[N],fir[N],ind[N],bel[N];
	bool vis[N];
	struct edge{
		int to,nx;
	}eg[N<<2];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void tarjan(const int x){
		static int top,cnd,stk[N],dfn[N],low[N];
		dfn[x]=low[x]=++cnd;
//		printf("dfn%d: %d\n",cnd,x);
		stk[++top]=x;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(dfn[y]){
				if(fa[x]!=y&&!vis[y]) apn(low[x],dfn[y]);
			}
			else{
				fa[y]=x;
				tarjan(y);
				apn(low[x],low[y]);
			}
		}
//		printf("%d: dfn%d low%d\n",x,dfn[x],low[x]);
		if(dfn[x]==low[x]){
			++cnf;
			for(int j=0;j!=x;){
				j=stk[top--];
				vis[j]=1;
				bel[j]=cnf;
			}
		}
	}

	inline int solve(){
		int ans=0;
		for(int i=1;i<=n;++i){
			for(int j=fir[i];j;j=eg[j].nx){
				if(bel[i]!=bel[eg[j].to]) ++ind[bel[i]];
			}
		}
		for(int i=1;i<=cnf;++i){
			if(ind[i]==1) ++ans;
		}
		return (ans+1)>>1;
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=m;++i){
		const int x=nxi(),y=nxi();
		G::add(x,y);
		G::add(y,x);
	}
	for(int i=1;i<=n;++i){
		if(!G::bel[i]) G::tarjan(i);
	}
	printf("%d\n",G::solve());
	return 0;
}
