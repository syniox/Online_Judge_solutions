#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=1e5+5;
int n,q;

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

namespace G{
	int cnt,fir[N<<1];
	struct edge{
		int to,nx;
	}eg[N<<2];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,fir[b]};
		fir[b]=cnt;
	}
}

namespace L{
	using namespace G;
	int dfn[N],idx[N],top[N],sz[N],fa[N],son[N],dep[N];

	void dfs_son(const int x){
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa[x]) continue;
			fa[y]=x;
			dep[y]=dep[x]+1;
			dfs_son(y);
			if(sz[y]>sz[son[x]]) son[x]=y;
			sz[x]+=sz[y];
		}
	}

	void dfs_top(const int x){
		static int cnd;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		dfn[x]=++cnd;
		idx[cnd]=x;
		if(son[x]) dfs_top(son[x]);
		for(int i=fir[x]; i; i=eg[i].nx){
			if(!top[eg[i].to]) dfs_top(eg[i].to);
		}
	}

	int jmp(int x,int t){
		while(dep[x]-dep[top[x]]<t){
			t-=dep[x]-dep[top[x]]+1;
			x=fa[top[x]];
		}
		return idx[dfn[x]-t];
	}

	int get_lca(int x,int y){
		while(top[x]!=top[y]){
			if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
			else y=fa[top[y]];
		}
		return dep[x]<dep[y]?x:y;
	}

	int get_dis(const int x,const int y){
		return dep[x]+dep[y]-(dep[get_lca(x,y)]<<1);
	}

	int get_mid(const int x,const int y){
		const int d=get_dis(x,y);
		return dep[x]>dep[y]?jmp(x,d):jmp(y,d);
	}
}

namespace T{
	using namespace G;
	int cur_sz,rt,xsz,sz[N*2],fa[N*2][18],dis[N*2][18],totf[N*2],dep[N*2],xdep[N*2];
	int *anss[N*2],*ansf[N*2],*sbuk[N*2];
	bool vis[N*2];

	void dfs_rt(const int x,const int f){
		int res=0;
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(vis[y]||y==f) continue;
			dfs_rt(y,x);
			apx(res,sz[y]);
			sz[x]+=sz[y];
		}
		apx(res,cur_sz-sz[x]);
		if(xsz>res) rt=x,xsz=res;
	}

	int get_rt(const int x,const int sz){
		cur_sz=sz;
		xsz=N*2;
		dfs_rt(x,x);
		return rt;
	}

	void dfs_xdep(const int x,const int f){
		fa[x][++totf[x]]=rt;
		dis[x][totf[x]]=dep[x];
		xdep[x]=dep[x];
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(vis[y]||y==f) continue;
			dep[y]=dep[x]+1;
			dfs_xdep(y,x);
			apx(xdep[x],xdep[y]);
		}
	}

	void dfs_ans(const int x,const int f){
		++sbuk[rt][dep[x]];
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!vis[y]&&y!=f) dfs_ans(y,x);
		}
	}

	int build(int x,const int csz){
		x=get_rt(x,csz);
		vis[x]=1;
		dep[x]=0;
		dfs_xdep(x,x);
		anss[x]=new int[xdep[x]+1];
		sbuk[x]=new int[xdep[x]+1];
		memset(anss[x],0,(xdep[x]+1)*sizeof(int));
		memset(sbuk[x],0,(xdep[x]+1)*sizeof(int));
		for(int i=fir[x]; i; i=eg[i].nx){
			int y=eg[i].to,d=xdep[y];
			if(vis[y]) continue;
			rt=x;
			dfs_ans(y,x);
			y=build(y,sz[y]);
			ansf[y]=new int[d+1];
			ansf[y][0]=sbuk[x][0];
			for(int i=1; i<=d; ++i){
				ansf[y][i]=ansf[y][i-1]+sbuk[x][i];
				anss[x][i]+=sbuk[x][i];
			}
		}
		for(int i=1; i<=xdep[x]; ++i){
			anss[x][i]+=anss[x][i-1];
		}
		if(sbuk[x]!=0){
			delete[] sbuk[x];
		}
		return 0;
	}

	int qans(int x,const int d){
		int ans=anss[x][std::min(xdep[x],d)];
		for(int i=totf[x]-1; i; --i){
			const int dep=std::min(xdep[fa[x][i]],d-dis[x][i]);
			ans+=anss[fa[x][i]][dep];
			ans-=ansf[fa[x][i+1]][dep];
		}
		return ans;
	}
}

int main(){
	freopen("d.in","r",stdin);
	n=nxi(),q=nxi();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,n+i),G::add(n+i,b);
	}
	L::dfs_son(1);
	L::dfs_top(1);
	T::build(1,n);
	for(int ans=0,i=1; i<=q; ++i){
		const int a=(nxi()+ans)%n+1,b=(nxi()+ans)%n+1,d=(nxi()+ans)%n;
		const int m=L::get_mid(a,b);
		printf("%d\n",ans=T::qans(a,d*2)-T::qans(b,d*2)-T::qans(m,d));
	}
	return 0;
}
