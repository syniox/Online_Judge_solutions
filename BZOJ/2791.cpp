#include <iostream>
#include <cstdio>
#include <cstring>
const int N=5e5+5;
const int P=19;
int n,q;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace U{
	int fa[N];

	int find_rt(const int x){
		return fa[x]?fa[x]=find_rt(fa[x]):x;
	}
	inline void link(int x,int y){
		x=find_rt(x),y=find_rt(y);
		if(x!=y) fa[x]=y;
	}
}

namespace G{
	int cnt,fir[N];
	int nxt[N][P],idx[N],mp[N],dep[N],dis[N],top[N],clen[N];
	bool vis[N],vis_f[N];
	struct edge{
		int to,nx;
	}eg[N];

	inline void init(){
		memset(dep,-1,sizeof(dep));
		memset(dis,-1,sizeof(dis));
	}

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	inline int jmp(int x,const int t){
		return x;
	}

	inline void get_nxt(){
		for(int i=1; i<P; ++i){
			for(int j=1; j<=n; ++j){
				nxt[j][i]=nxt[nxt[j][i-1]][i-1];
			}
		}
	}

	inline void get_cir(){
		for(int x=1; x<=n; ++x){
			int rt=U::find_rt(x);
			if(vis_f[rt]) continue;
			vis_f[rt]=1;
			for(; !vis[x]; x=nxt[x][0]){
				vis[x]=1;
			}
			dep[x]=0,dis[x]=1;
			int len=1;
			for(int i=x; nxt[i][0]!=x; i=nxt[i][0]){
				dep[nxt[i][0]]=0;
				len=dis[nxt[i][0]]=dis[i]+1;
			}
			clen[x]=len;
			for(int i=nxt[x][0]; i!=x; i=nxt[i][0]){
				clen[i]=len;
			}
		}
	}

	inline void dfs_dep(const int x){
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(dep[y]==-1){
				top[y]=top[x];
				dep[y]=dep[x]+1;
				dfs_dep(y);
			}
		}
	}

	inline void get_dep(){
		for(int i=1; i<=n; ++i){
			if(dep[i]==0) top[i]=i,dfs_dep(i);
		}
	}

	inline int get_lca(int x,int y){
		if(dep[x]<dep[y]) std::swap(x,y);
		int t=dep[x]-dep[y];
		for(int i=0; i<P; ++i){
			if(t>>i&1) x=nxt[x][i];
		}
		if(x==y) return x;
		for(int i=P-1; ~i; --i){
			if(nxt[x][i]!=nxt[y][i]){
				x=nxt[x][i];
				y=nxt[y][i];
			}
		}
		return nxt[x][0];
	}

	inline void solve(const int x,const int y){
		if(top[x]==top[y]){
			int lca=get_lca(x,y);
			printf("%d %d\n",dep[x]-dep[lca],dep[y]-dep[lca]);
			return;
		}
		const int pos_x=dis[top[x]];
		const int pos_y=dis[top[y]];
		const int len=clen[top[x]];

		const int dis1=pos_y>pos_x?pos_y-pos_x:pos_y+len-pos_x;
		const int dis2=pos_x>pos_y?pos_x-pos_y:pos_x+len-pos_y;

		const int xlen1=std::max(dep[y],dep[x]+dis1);
		const int xlen2=std::max(dep[x],dep[y]+dis2);
		
		if(xlen1!=xlen2){
			if(xlen1<xlen2) printf("%d %d\n",dep[x]+dis1,dep[y]);
			else printf("%d %d\n",dep[x],dep[y]+dis2);
			return;
		}
		const int nlen1=std::min(dep[y],dep[x]+dis1);
		const int nlen2=std::min(dep[x],dep[y]+dis2);
		if(nlen1!=nlen2){
			if(nlen1<nlen2) printf("%d %d\n",dep[x]+dis1,dep[y]);
			else printf("%d %d\n",dep[x],dep[y]+dis2);
		}
		else printf("%d %d\n",dep[x]+dis1,dep[y]);
	}
}

int main(){
	n=nxi(),q=nxi();
	G::init();
	for(int i=1; i<=n; ++i){
		G::nxt[i][0]=nxi();
		U::link(i,G::nxt[i][0]);
		G::add(G::nxt[i][0],i);
	}
	G::get_nxt();
	G::get_cir();
	G::get_dep();
	for(int i=1; i<=q; ++i){
		const int x=nxi(),y=nxi();
		if(U::find_rt(x)!=U::find_rt(y)){
			puts("-1 -1");
			continue;
		}
		G::solve(x,y);
	}
	return 0;
}
