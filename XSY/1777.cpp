#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
const int N=1e5+5;
int n,q,m,bel[N];
unsigned hsh[N];
std::vector <int> col[N];

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

namespace H{
	const unsigned P=131;
	unsigned val[N],*pt=val;

	inline unsigned get_hash(char *ch,int len){
		unsigned ans=0;
		for(int i=0; i<len; ++i){
			ans=ans*P+ch[i]-'A';
		}
		return ans;
	}
	inline void insert(unsigned v){
		*pt++=v;
	}
	inline void build(){
		std::sort(val,pt);
		pt=std::unique(val,pt);
	}
	inline int ask(unsigned v){
		unsigned *t=std::lower_bound(val,pt,v);
		return *t==v?t-val+1:0;
	}
}

namespace G{
	int cnt,fir[N],rad_a[N],rad_b[N],rad_l[N];
	int fa[N],sz[N],son[N],top[N],dep[N];
	struct edge{
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
				fa[y]=x;
				dep[y]=dep[x]+1;
				dfs_son(y);
				if(sz[y]>sz[son[x]]) son[x]=y;
				sz[x]+=sz[y];
			}
		}
	}

	void dfs_top(const int x){
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		if(son[x]) dfs_top(son[x]);
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!top[y]) dfs_top(y);
		}
	}

	inline int getlca(int x,int y){
		while(top[x]!=top[y]){
			dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]];
		}
		return dep[x]<dep[y]?x:y;
	}

	inline int getdis(const int x,const int y){
		if(!x||!y) return 0;
		return dep[x]+dep[y]-(dep[getlca(x,y)]<<1);
	}

	inline void get_rad(){
		for(int i=1; i<=m; ++i){
			std::vector <int> ::iterator it;
			for(it=col[i].begin(); it!=col[i].end(); ++it){
				if(!rad_a[i]){
					rad_a[i]=*it;
					continue;
				}
				if(!rad_b[i]){
					rad_b[i]=*it;
					continue;
				}
				if(getdis(*it,rad_b[i])>getdis(rad_a[i],rad_b[i])){
					rad_a[i]=*it;
				}
				if(getdis(*it,rad_a[i])>getdis(rad_a[i],rad_b[i])){
					rad_b[i]=*it;
				}
			}
		}
	}

	inline int ask_rad(const int x,const int y){
		int ans0=std::max(getdis(rad_a[x],rad_a[y]),getdis(rad_a[x],rad_b[y]));
		int ans1=std::max(getdis(rad_b[x],rad_a[y]),getdis(rad_b[x],rad_b[y]));
		return std::max(ans0,ans1);
	}
}

int main(){
	static char str[6];
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		scanf("%s",str);
		hsh[i]=H::get_hash(str,strlen(str));
		H::insert(hsh[i]);
	}
	H::build();
	for(int i=1; i<=n; ++i){
		bel[i]=H::ask(hsh[i]);
		apx(m,bel[i]);
		col[bel[i]].push_back(i);
	}
	for(int a,b,i=1; i<n; ++i){
		a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	G::dfs_son(1);
	G::dfs_top(1);
	G::get_rad();
	for(int x,y,i=1; i<=q; ++i){
		scanf("%s",str),x=H::ask(H::get_hash(str,strlen(str)));
		scanf("%s",str),y=H::ask(H::get_hash(str,strlen(str)));
		if(!x||!y) puts("-1");
		else printf("%d\n",G::ask_rad(x,y)+1);
	}
	return 0;
}
