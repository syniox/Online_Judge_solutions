#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
int n,lim_l[N],lim_r[N],ans[N];
bool dif;

namespace utils{
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

namespace G{
	int cnt,fir[N],fa[N],dep[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		//printf("add: %d %d\n",a,b);
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs_dep(const int x){
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa[x]) continue;
			fa[y]=x;
			dep[y]=dep[x]+1;
			dfs_dep(y);
		}
	}

	bool dfs_vld(const int x){
		if(lim_r[x]==-1){
			lim_r[x]=((dep[x]&1)==dif?1e5+2:1e5+1);
			lim_l[x]=((dep[x]&1)==dif?-1e5-2:-1e5-1);
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa[x]) continue;
			if(!dfs_vld(y)) return 0;
			apn(lim_r[x],lim_r[y]+1);
			apx(lim_l[x],lim_l[y]-1);
		}
		assert(((lim_l[x]^lim_r[x])&1)==0);
		return lim_l[x]<=lim_r[x];
	}

	void dfs_ans(const int x){
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa[x]) continue;
			ans[y]=ans[x]<lim_l[y]?ans[x]+1:ans[x]-1;
			dfs_ans(y);
		}
	}
}

int main(){
	n=nxi();
	memset(lim_r+1,-1,n*sizeof(int));
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	G::dfs_dep(1);
	for(int q=nxi(),i=1; i<=q; ++i){
		const int x=nxi(),v=nxi();
		lim_l[x]=lim_r[x]=v;
		if(i==1) dif=(v&1)^(G::dep[x]&1);
		else if(((v&1)^(G::dep[x]&1))!=dif){
			puts("No");
			return 0;
		}
	}
	if(!G::dfs_vld(1)){
		puts("No");
		return 0;
	}
	ans[1]=lim_l[1];
	G::dfs_ans(1);
	puts("Yes");
	for(int i=1; i<=n; ++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}
