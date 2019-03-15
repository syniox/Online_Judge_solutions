#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
const int N=1e5+5;
int n,m,dp[N];
class _Route{
	public:
		int x,y,v;
};

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,fir[N],fa[N];
	int sz[N],dfn[N],son[N],top[N],dep[N];
	std::vector <_Route> rot[N];
	class edge{
		public:
			int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs_son(const int x){
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!sz[y]){
				dep[y]=dep[x]+1;
				fa[y]=x;
				dfs_son(y);
				if(sz[y]>sz[son[x]]) son[x]=y;
				sz[x]+=sz[y];
			}
		}
	}

	void dfs_top(const int x){
		static int cnd;
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
			dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]];
		}
		return dep[x]<dep[y]?x:y;
	}

	inline int get_rot_v(int x,const int f,int *sum){
		int res=0;
		for(; top[x]!=top[f]; x=fa[top[x]]){
			res+=sum[top[x]]-sum[son[x]];
		}
		return res+sum[f]-sum[son[x]];
	}

	void dfs_ans(const int x){
		static int dp_s[N],nxt_s[N],nxt_dp[N];
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa[x]) continue;
			dfs_ans(y);
			dp_s[x]+=dp[y];
		}
		nxt_dp[x]=nxt_dp[son[x]];
		nxt_s[x]=dp_s[x]+nxt_s[son[x]];
		dp[x]=dp_s[x];
		for(std::vector <_Route> ::iterator it=rot[x].begin(); it!=rot[x].end(); ++it){
			int res=0;
			res+=get_rot_v(it->x,x,nxt_s),res-=get_rot_v(it->x,x,nxt_dp);
			res+=get_rot_v(it->y,x,nxt_s),res-=get_rot_v(it->y,x,nxt_dp);
			apx(dp[x],res-dp_s[x]+it->v);
		}
		nxt_dp[x]+=dp[x];
	}
}

int main(){
	n=nxi();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	G::dfs_son(1);
	G::dfs_top(1);
	m=nxi();
	for(int i=1; i<=m; ++i){
		const int x=nxi(),y=nxi(),v=nxi();
		G::rot[G::get_lca(x,y)].push_back((_Route){x,y,v});
	}
	G::dfs_ans(1);
	printf("%d\n",dp[1]);
	return 0;
}
