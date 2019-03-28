#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <vector>
#include <cassert>
#include <sys/mman.h>
#include <unistd.h>
typedef long long lint;
const int N=1e5+5;
int n,m,cap,wgt[N],hbit[N];
bool type;

struct data{
	int x;
	lint dis;
	friend bool operator < (const data &a,const data &b){
		return a.dis>b.dis;
	}
};

namespace IO{
	char *pt;
	struct _Init{
		_Init(){pt=(char*)mmap(0,lseek(0,0,SEEK_END),PROT_READ,MAP_PRIVATE,0,0);}
	}_init;
	inline int nxi(){
		int x=0;
		char c;
		while((c=*pt++)>'9'||c<'0');
		while(x=x*10-48+c,(c=*pt++)>='0'&&c<='9');
		return x;
	}
}
using IO::nxi;

inline void init(){
	for(int i=2; i<=n; ++i){
		hbit[i]=hbit[i>>1]+1;
	}
}

namespace G{
	int cnt=1,fir[N],dep[N],fa[N][19],dom[N][19];
	int dfn[N],idx[N];
	lint dis[N];
	std::vector <int> from[N],nxt[N];
	struct edge{
		int to,wi,nx;
	}eg[N<<2];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	inline bool cmp_wgt(int a,int b){
		return wgt[a]<wgt[b];
	}

	inline bool cmp_dis(int a,int b){
		return dis[a]<dis[b];
	}

	void dfs_dfn(const int x){
		static int cnd;
		dfn[x]=++cnd;
		idx[cnd]=x;
		for(int i=1; i<19&&fa[x][i-1]; ++i){
			fa[x][i]=fa[fa[x][i-1]][i-1];
		}
		for(std::vector <int> ::iterator it=nxt[x].begin(); it!=nxt[x].end(); ++it){
			if(!dfn[*it]){
				fa[*it][0]=x;
				dep[*it]=dep[x]+1;
				dfs_dfn(*it);
			}
		}
	}

	inline int get_lca(int x,int y){
		if(dep[x]<dep[y]) std::swap(x,y);
		int tmp=dep[x]-dep[y];
		for(int i=0; 1<<i<=tmp; ++i){
			if(tmp>>i&1) x=fa[x][i];
		}
		if(x==y) return x;
		for(int i=18; ~i; --i){
			if(fa[x][i]!=fa[y][i]){
				x=fa[x][i];
				y=fa[y][i];
			}
		}
		return fa[x][0];
	}

	inline int get_dom(int x,const int f){
		int tmp=dep[x]-dep[f]+1;
		int ans=dom[x][0];
		for(int i=0; 1<<i<=tmp; ++i){
			if(tmp>>i&1){
				if(dfn[ans]>dfn[dom[x][i]]) ans=dom[x][i];
				x=fa[x][i];
			}
		}
		return ans;
	}

	void build_dfn(){
		static bool vis[N];
		std::priority_queue <data> pq;
		memset(dis,10,sizeof(dis));
		dis[cap]=0;
		pq.push((data){cap,0});
		while(!pq.empty()){
			data x=pq.top();
			pq.pop();
			if(vis[x.x]) continue;
			vis[x.x]=1;
			for(int i=fir[x.x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				const lint v=eg[i].wi+dis[x.x];
				if(dis[y]>v){
					dis[y]=v;
					from[y].clear();
					pq.push((data){y,v});
				}
				if(dis[y]==v){
					from[y].push_back(x.x);
				}
			}
		}
		for(int i=1; i<=n; ++i){
			std::vector <int> ::iterator it;
			for(it=from[i].begin(); it!=from[i].end(); ++it){
				nxt[*it].push_back(i);
			}
		}
		for(int i=1; i<=n; ++i){
			std::sort(nxt[i].begin(),nxt[i].end(),cmp_wgt);
		}
		dfn[0]=1e7;
		dfs_dfn(cap);
	}

	void build_dom(){
		static int que[N];
		for(int i=1; i<=n; ++i){
			que[i]=dom[i][0]=i;
		}
		std::sort(que+1,que+n+1,cmp_dis);
		for(int i=1; i<=n; ++i){
			const int x=que[i];
			for(int j=1; j<19&&fa[x][j-1]; ++j){
				int pf=fa[x][j-1];
				fa[x][j]=fa[pf][j-1];
				dom[x][j]=dom[x][j-1];
				if(dep[dom[pf][j-1]]<dep[dom[x][j]]){
					dom[x][j]=dom[pf][j-1];
				}
			}
			std::vector <int> ::iterator it;
			for(it=nxt[x].begin(); it!=nxt[x].end(); ++it){
				if(fa[*it][0]==x) continue;
				int lca=get_lca(x,*it);
				int res=get_dom(x,lca);
				if(dfn[dom[*it][0]]>dfn[res]){
					dom[*it][0]=res;
				}
			}
		}
	}

	inline int ask(const int x,const int y){
		int p=y,lim=hbit[dep[y]-dep[x]];
		for(int j=lim; ~j; --j){
			if(dep[p]-dep[x]<1<<j) continue;
			if(dfn[dom[p][j]]>dfn[x]) p=fa[p][j]; 
		}
		return dep[p]-dep[x];
	}
}

int main(){
	n=nxi(),m=nxi(),cap=nxi(),type=nxi();
	init();
	for(int i=1; i<=n; ++i){
		wgt[i]=nxi();
	}
	for(int i=1; i<=m; ++i){
		const int a=nxi(),b=nxi(),v=nxi();
		G::add(a,b,v);
		G::add(b,a,v);
	}
	G::build_dfn();
	G::build_dom();
	for(int ans=0,q=nxi(); q; --q){
		int x=nxi(),y=nxi();
		if(type) x^=ans,y^=ans;
		printf("%d\n",ans=G::ask(x,y));
		assert(ans>=0);
	}
	return 0;
}
