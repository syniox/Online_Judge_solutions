#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
const int N=1e6+5;
int n,m,bel[N];
bool fine[N];

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline char get_c(){
	static char *h,*t,buf[20000];
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=get_c())>'9'||c<'0');
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnf;
	bool vis[N];
	std::vector <int> zg[N],fg[N];

	void tarjan(const int x){
		static int cnd,top,stk[N],dfn[N],low[N];
		dfn[x]=low[x]=++cnd;
		stk[++top]=x;
		for(int i=0; i<(int)zg[x].size(); ++i){
			const int y=zg[x][i];
			if(!dfn[y]){
				tarjan(y);
				apn(low[x],low[y]);
			}
			else{
				if(!vis[y]) apn(low[x],dfn[y]);
			}
		}
		if(dfn[x]==low[x]){
			++cnf;
			for(int i=stk[top--]; ~top; i=stk[top--]){
				bel[i]=cnf;
				vis[i]=1;
				if(i==x) break;
			}
		}
	}
}

namespace D{
	int seq[N];
	bool ind[N];
	std::vector <int> gr[N];

	inline void init(){
		for(int i=1;i<=n;++i){
			gr[i].clear();
		}
		memset(ind,0,sizeof(ind));
	}

	inline void build(const std::vector <int> vt[N]){
		for(int i=1; i<=n; ++i){
			for(int j=vt[i].size()-1; ~j; --j){
				int tgt=bel[vt[i][j]];
				if(bel[i]!=tgt){
					gr[bel[i]].push_back(tgt);
				}
			}
		}
	}

	inline void solve(){
		int cnt=0;
		for(int i=1; i<=G::cnf; ++i){
			const int x=seq[i];
			for(int j=gr[x].size()-1; ~j; --j){
				if(!ind[gr[x][j]]) --cnt;
				ind[gr[x][j]]=1;
			}
			if(cnt++) fine[x]=0;
		}
	}
}

int main(){
	memset(fine,1,sizeof(fine));
	n=nxi(),m=nxi();
	for(int i=1; i<=m; ++i){
		const int x=nxi(),y=nxi();
		G::zg[x].push_back(y);
		G::fg[y].push_back(x);
	}
	for(int i=1; i<=n; ++i){
		if(!G::vis[i]) G::tarjan(i);
	}
	for(int i=1; i<=G::cnf; ++i){
		D::seq[i]=i;
	}
	D::build(G::zg);
	D::solve();
	std::reverse(D::seq+1,D::seq+G::cnf+1);
	D::init();
	D::build(G::fg);
	D::solve();
	int ans=0;
	for(int i=1;i<=n;++i){
		ans+=fine[bel[i]];
	}
	printf("%d\n",ans);
	for(int i=1;i<=n;++i){
		if(fine[bel[i]]) printf("%d ",i);
	}
	puts("");
	return 0;
}
