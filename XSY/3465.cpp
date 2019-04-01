#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <queue>
#include <sys/mman.h>
#include <unistd.h>
typedef long long lint;
const int N=1e5+5;
int n,m,qs,qt;
lint dis[N],disf[N],ans[N];
//disf: 删去连向fa的边之后的最短路

namespace IO{
	char *ibuf;
	struct _Init{
		_Init(){ibuf=(char*)mmap(0,lseek(0,0,SEEK_END),PROT_READ,MAP_PRIVATE,0,0);}
	}_init;
	inline int nxi(){
		int x=0;
		char c;
		while((c=*ibuf++)>'9'||c<'0');
		while(x=x*10-48+c,(c=*ibuf++)>='0'&&c<='9');
		return x;
	}
}
using IO::nxi;

template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

namespace H{
	int cnt,rt[N];
	class node{
		public:
			lint tag,val;
			int ls,rs,expr,dep;
	}tr[N<<2];

	inline void get_psh(const int x,const lint v){
		tr[x].tag+=v;
		tr[x].val+=v;
	}

	inline void psh(const int x){
		if(!tr[x].tag) return;
		if(tr[x].ls) get_psh(tr[x].ls,tr[x].tag);
		if(tr[x].rs) get_psh(tr[x].rs,tr[x].tag);
		tr[x].tag=0;
	}

	inline int merge(int x,int y){
		if(!x||!y) return x+y;
		if(tr[x].val>tr[y].val) std::swap(x,y);
		psh(x);
		tr[x].rs=merge(tr[x].rs,y);
		if(tr[tr[x].rs].dep>tr[tr[x].ls].dep){
			std::swap(tr[x].ls,tr[x].rs);
		}
		tr[x].dep=tr[tr[x].rs].dep+1;
		return x;
	}

	inline void insert(int x,lint v,const int expr){
		tr[++cnt]=(node){0,v,0,0,expr,1};
		rt[x]=merge(rt[x],cnt);
	}
}

namespace T{
	int cnt=1,fir[N],fa[N],dep[N],sz[N],son[N],top[N];
	struct edge{
		int to,wi,nx;
	}eg[N<<1];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	void dfs_son(const int x){
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa[x]) continue;
			dep[y]=dep[x]+1;
			dfs_son(y);
			if(sz[y]>sz[son[x]]) son[x]=y;
			sz[x]+=sz[y];
		}
	}

	void dfs_top(const int x){
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
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

	void dfs_dis(const int x){
		using H::tr;
		using H::rt;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa[x]) continue;
			dfs_dis(y);
			if(rt[y]){
				H::get_psh(rt[y],eg[i].wi);
				rt[x]=H::merge(rt[x],rt[y]);
			}
		}
		while(rt[x]&&tr[rt[x]].expr>=dep[x]){
			rt[x]=H::merge(tr[rt[x]].ls,tr[rt[x]].rs);
		}
		disf[x]=rt[x]?tr[rt[x]].val:1e16;
	}
}

namespace G{
	int cnt=1,fir[N];
	bool vis[N],intr[N<<1];
	struct edge{
		int to,wi,nx;
	}eg[N<<2];

	struct _pair{
		int x;
		lint y;
		friend bool operator < (const _pair &a,const _pair &b){
			return a.y>b.y;
		}
	};

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	void build_tr(){
		static std::priority_queue <_pair> pq;
		memset(dis,10,sizeof(dis));
		memset(vis,0,sizeof(vis));
		dis[qt]=0;
		pq.push((_pair){qt,0});
		while(!pq.empty()){
			const _pair x=pq.top();
			pq.pop();
			if(vis[x.x]) continue;
			vis[x.x]=1;
			for(int i=fir[x.x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				const lint v=x.y+eg[i].wi;
				if(dis[y]>v){
					dis[y]=v,T::fa[y]=x.x;
					pq.push((_pair){y,v});
				}
			}
		}
		for(int i=1; i<=n; ++i){
			if(i!=qt){
				T::add(T::fa[i],i,dis[i]-dis[T::fa[i]]);
			}
		}
		for(int i=1; i<=m; ++i){
			const int x(eg[i<<1].to),y(eg[i<<1|1].to);
			if(T::fa[x]==y||T::fa[y]==x) intr[i]=1;
		}
	}

	void get_ans(){
		static std::priority_queue <_pair> pq;
		memset(vis+1,0,n*sizeof(bool));
		memset(ans+1,10,n*sizeof(lint));
		ans[qt]=0;
		pq.push((_pair){qt,0});
		while(!pq.empty()){
			const _pair x=pq.top();
			pq.pop();
			if(vis[x.x]) continue;
			vis[x.x]=1;
			for(int i=fir[x.x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				const lint v=std::max(disf[y],x.y+eg[i].wi);
				if(ans[y]>v){
					ans[y]=v;
					pq.push((_pair){y,v});
				}
			}
		}
	}
}

int main(){
	n=nxi(),m=nxi(),qs=nxi(),qt=nxi();
	for(int i=1; i<=m; ++i){
		const int a=nxi(),b=nxi(),v=nxi();
		G::add(a,b,v);
		G::add(b,a,v);
	}
	G::build_tr();
	T::dfs_son(qt);
	T::dfs_top(qt);
	for(int i=1; i<=m; ++i){
		if(G::intr[i]) continue;
		const int x=G::eg[i<<1].to,y=G::eg[i<<1|1].to;
		const int v=G::eg[i<<1].wi;
		const int lca=T::get_lca(x,y);
		if(x!=lca) H::insert(x,dis[y]+v,T::dep[lca]);
		if(y!=lca) H::insert(y,dis[x]+v,T::dep[lca]);
	}
	T::dfs_dis(qt);
	disf[qt]=0;
	G::get_ans();
	printf("%lld\n",ans[qs]<1e16?ans[qs]:-1);
	return 0;
}
