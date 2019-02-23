#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
const int N=2e5+5;
int n;

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int st_f,st_s,dep[N],xdis;
	int fa[N],sz[N],son[N],top[N];
	std::vector <int> vf[N],vs[N];

	inline int get_lca(int x,int y){
		while(top[x]!=top[y]){
			dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]];
		}
		return dep[x]<dep[y]?x:y;
	}

	inline int get_dis(const int x,const int y){
		return dep[x]+dep[y]-(dep[get_lca(x,y)]<<1);
	}

	void dfs_sz(const int x){
		sz[x]=1;
		for(std::vector <int> ::iterator it=vs[x].begin(); it!=vs[x].end(); ++it){
			if(!sz[*it]){
				dep[*it]=dep[x]+1;
				fa[*it]=x;
				dfs_sz(*it);
				if(sz[*it]>sz[son[x]]) son[x]=*it;
				sz[x]+=sz[*it];
			}
		}
	}

	void dfs_top(const int x){
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		for(std::vector <int> ::iterator it=vs[x].begin(); it!=vs[x].end(); ++it){
			if(!top[*it]) dfs_top(*it);
		}
	}

	bool dfs_free(const int x,const int fa,const int dis){
		std::vector <int> ::iterator it;
		if(dis<dep[x]){
			for(it=vf[x].begin(); it!=vf[x].end(); ++it){
				if(get_dis(x,*it)>2) return 1;
			}
		}
		for(it=vf[x].begin(); it!=vf[x].end(); ++it){
			if(*it!=fa&&dis+1<dep[*it]){
				if(dfs_free(*it,x,dis+1)) return 1;
			}
		}
		return 0;
	}

	void dfs_xdis(const int x,const int fa,const int dis){
		apx(xdis,dep[x]);
		for(std::vector <int> ::iterator it=vf[x].begin(); it!=vf[x].end(); ++it){
			if(*it==fa) continue;
			if(dis+1==dep[*it]) apx(xdis,dis+1);
			if(dis+1<dep[*it]){
				dfs_xdis(*it,x,dis+1);
			}
		}
	}
}

int main(){
	n=nxi();
	G::st_f=nxi(),G::st_s=nxi();
	for(int i=1; i<n; ++i){
		const int x=nxi(),y=nxi();
		G::vf[x].push_back(y);
		G::vf[y].push_back(x);
	}
	for(int i=1; i<n; ++i){
		const int x=nxi(),y=nxi();
		G::vs[x].push_back(y);
		G::vs[y].push_back(x);
	}
	G::dfs_sz(G::st_s);
	G::dfs_top(G::st_s);
	if(G::dfs_free(G::st_f,0,0)){
		puts("-1");
		return 0;
	}
	G::dfs_xdis(G::st_f,0,0);
	printf("%d\n",G::xdis<<1);
	return 0;
}
