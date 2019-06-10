#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=30005;
int n,val[N];

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
	int cnt,fir[N];
	int cur_sz,rt,sz[N],xsz_rt,fa[N][17],dis_fa[N][17],cfa[N];
	int cnts[N][15][2],cntf[N][15][2];
	lint ans,sums[N][15][2],sumf[N][15][2];
	bool vis[N];
	struct edge{
		int to,wi,nx;
	}eg[N<<1];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	void dfs_rt(const int x,const int f){
		int xsz=0;
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(vis[y]||y==f) continue;
			dfs_rt(y,x);
			sz[x]+=sz[y];
			apx(xsz,sz[y]);
		}
		apx(xsz,cur_sz-sz[x]);
		if(xsz<xsz_rt) rt=x,xsz_rt=xsz;
	}

	int get_rt(const int x,const int sz){
		xsz_rt=1e9;
		cur_sz=sz;
		dfs_rt(x,0);
		return rt;
	}

	void dfs_dis(const int x,const int f,const int dis){
		fa[x][++cfa[x]]=rt;
		dis_fa[x][cfa[x]]=dis;
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=f&&!vis[y]){
				dfs_dis(y,x,dis+eg[i].wi);
				sz[x]+=sz[y];
			}
		}
	}

	void build(int x,const int sz){
		x=get_rt(x,sz);
		vis[x]=1;
		dfs_dis(x,0,0);
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!vis[y]) build(y,G::sz[y]);
		}
	}

	void upd(const int x,const int w){
		lint res=0;
		for(int i=0; i<15; ++i){
			res+=(1ll<<i)*sums[x][i][(val[x]>>i&1)^1];
		}
		for(int i=cfa[x]; i>1; --i){
			const int f=fa[x][i],ff=fa[x][i-1],d=dis_fa[x][i-1];
			lint tmp=0;
			for(int j=0; j<15; ++j){
				const int p=val[x]>>j&1;
				tmp+=(1ll<<j)*(cnts[ff][j][p^1]-cntf[f][j][p^1]);
				res+=(1ll<<j)*(sums[ff][j][p^1]-sumf[f][j][p^1]);
			}
			res+=tmp*d;
		}
		for(int i=cfa[x]; i; --i){
			const int f=fa[x][i],d=dis_fa[x][i]*w;
			for(int j=0; j<15; ++j){
				sums[f][j][val[x]>>j&1]+=d;
				cnts[f][j][val[x]>>j&1]+=w;
			}
			if(i==1) break;
			const int e=dis_fa[x][i-1]*w;
			for(int j=0; j<15; ++j){
				sumf[f][j][val[x]>>j&1]+=e;
				cntf[f][j][val[x]>>j&1]+=w;
			}
		}
		ans+=res*w;
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi(),v=nxi();
		G::add(a,b,v);
		G::add(b,a,v);
	}
	G::build(1,n);
	for(int i=1; i<=n; ++i){
		G::upd(i,1);
	}
	for(int q=nxi(); q; --q){
		const int x=nxi(),v=nxi();
		G::upd(x,-1);
		val[x]=v;
		G::upd(x,1);
		printf("%lld\n",G::ans);
	}
	return 0;
}
