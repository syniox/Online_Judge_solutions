#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e5+5;
int n,m,ttog[N],ans[N*10];
bool used[N*10];

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

namespace T{
	int cnt=1,cnd,fir[N],dep[N],fa_e[N],fa[N][17],mx[N][17],pt[N];
	struct edge{
		int to,wi,nx;
	}eg[N<<1];
	struct node{
		int ls,rs,v,dep,rm;
	}tr[N*20];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	int merge(int x,int y){
		if(!x||!y) return x+y;
		if(tr[x].v>tr[y].v) std::swap(x,y);
		tr[x].rs=merge(tr[x].rs,y);
		if(tr[tr[x].ls].dep<tr[tr[x].rs].dep){
			std::swap(tr[x].ls,tr[x].rs);
		}
		tr[x].dep=tr[tr[x].rs].dep+1;
		return x;
	}

	void dfs(const int x){
		for(int i=1; fa[x][i-1]; ++i){
			fa[x][i]=fa[fa[x][i-1]][i-1];
			mx[x][i]=std::max(mx[x][i-1],mx[fa[x][i-1]][i-1]);
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa[x][0]) continue;
			fa[y][0]=x;
			mx[y][0]=eg[i].wi;
			fa_e[y]=i>>1;
			dep[y]=dep[x]+1;
			dfs(y);
		}
	}

	int get_lca(int x,int y){
		if(dep[x]<dep[y]) std::swap(x,y);
		int depd=dep[x]-dep[y];
		for(int i=0; 1<<i<=depd; ++i){
			if(depd>>i&1) x=fa[x][i];
		}
		if(x==y) return x;
		for(int i=16; ~i; --i){
			if(fa[x][i]!=fa[y][i]){
				x=fa[x][i];
				y=fa[y][i];
			}
		}
		return fa[x][0];
	}

	int get_mx(int x,int f){
		if(x==f) return 0;
		int depd=dep[x]-dep[f],ans=0;
		for(int i=16; ~i; --i){
			if(depd>>i&1){
				apx(ans,mx[x][i]);
				x=fa[x][i];
			}
		}
		return ans;
	}

	void addq(const int x,const int v,const int rm_dep){
		tr[++cnd]=(node){0,0,v,0,rm_dep};
		pt[x]=merge(pt[x],cnd);
	}

	void solve_used(const int x){
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(dep[y]<dep[x]) continue;
			solve_used(y);
			ans[ttog[i>>1]]=pt[y]?tr[pt[y]].v:1e9;
			pt[x]=merge(pt[x],pt[y]);
		}
		while(pt[x]&&tr[pt[x]].rm>=dep[x]){
			pt[x]=merge(tr[pt[x]].ls,tr[pt[x]].rs);
		}
	}
}

namespace G{
	int fa[N];
	struct edge{
		int id,x,y,v;
		friend bool operator < (const edge &a,const edge &b){
			return a.v<b.v;
		}
	}eg[N*10];

	int find_rt(const int x){
		return fa[x]?fa[x]=find_rt(fa[x]):x;
	}

	void kruskal(){
		std::sort(eg+1,eg+m+1);
		int cnt=0;
		for(int i=1; i<=m; ++i){
			const int x=find_rt(eg[i].x),y=find_rt(eg[i].y);
			if(x==y) continue;
			ttog[++cnt]=eg[i].id;
			used[eg[i].id]=1;
			T::add(eg[i].x,eg[i].y,eg[i].v);
			T::add(eg[i].y,eg[i].x,eg[i].v);
			fa[x]=y;
		}
	}

	void solve_unused(){
		for(int i=1; i<=m; ++i){
			if(used[eg[i].id]) continue;
			const int x=eg[i].x,y=eg[i].y,lca=T::get_lca(x,y);
			T::addq(x,eg[i].v,T::dep[lca]);
			T::addq(y,eg[i].v,T::dep[lca]);
			ans[eg[i].id]=std::max(T::get_mx(x,lca),T::get_mx(y,lca));
		}
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=m; ++i){
		int a=nxi(),b=nxi();
		G::eg[i]=(G::edge){i,a,b,nxi()};
	}
	G::kruskal();
	T::dfs(1);
	G::solve_unused();
	T::solve_used(1);
	for(int i=1; i<=m; ++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}
