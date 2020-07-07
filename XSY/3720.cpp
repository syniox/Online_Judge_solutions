#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
typedef long long lint;
using namespace std;
const int N=1e5+5;
int n;
lint abuk[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

namespace T1{
	int cnt,fir[N],fa[N];
	int sz[N],son[N],dep[N],top[N],dfn[N],idx[N];
	lint dis[N];
	struct edge{
		int to,wi,nx;
	}eg[N<<1];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}
	inline bool cmp_dfn(const int a,const int b){
		return dfn[a]<dfn[b];
	}

	void dfs_son(const int x){
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa[x]) continue;
			fa[y]=x;
			dis[y]=dep[x]+eg[i].wi;
			dep[y]=dep[x]+1;
			dfs_son(y);
			if(sz[y]>sz[son[x]]) son[x]=y;
			sz[x]+=sz[y];
		}
	}
	void dfs_top(const int x){
		static int cnd;
		dfn[x]=++cnd,idx[cnd]=x;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		if(!son[x]) return;
		dfs_top(son[x]);
		for(int i=fir[x]; i; i=eg[i].nx){
			if(!dfn[eg[i].to]) dfs_top(eg[i].to);
		}
	}

	inline int qlca(int x,int y){
		while(top[x]!=top[y]){
			dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]];
		}
		return dep[x]<dep[y]?x:y;
	}

	int tick,tag[N];
	vector<pair<int,lint> > vg[N];
	lint *val,dpd[N],dpu[N];

	inline void upd(const int x){
		if(tag[x]!=tick){
			dpd[x]=dpu[x]=1e15;
			vg[x].clear();
		}
	}
	inline void setf(const int x,const int f){
		apn(dpd[x],val[x]);
		vg[f].push_back(make_pair(x,dis[x]-dis[f]));
		apn(dpd[f],dpd[x]+dis[x]-dis[f]);
	}

	void vmain(int *ls,const int cls,lint *val){
		static int pbuk[N],stk[N];//pbuk: 退栈序列
		T1::val=val;
		++tick;
		std::sort(ls+1,ls+cls+1,cmp_dfn);
		int top=0,cpb=0;
		stk[++top]=ls[1];
		upd(ls[1]);
		for(int i=2; i<=cls; ++i){
			int lca=qlca(ls[i],stk[top]);
			upd(lca),upd(ls[i]);
			for(; top&&dep[stk[top]]>dep[lca]; --top){
				setf(stk[top],top>1&&dep[stk[top-1]]<dep[lca]?stk[top-1]:lca);
				pbuk[++cpb]=stk[top];
			}
			if(lca!=stk[top]) stk[++top]=lca;
			assert(lca!=ls[i]);
			stk[++top]=ls[i];
		}
		for(; top; --top){
			pbuk[++cpb]=stk[top];
			if(top>1) setf(stk[top],stk[top-1]);
		}
		for(int pidx=cpb,x=pbuk[pidx]; pidx; x=pbuk[--pidx]){
			static lint nl[N],nr[N];
			const int sz=vg[x].size();
			apn(abuk[x],val[x]+std::min(dpd[x],dpu[x]));
			apn(dpu[x],val[x]);
			for(int i=0; i<sz; ++i){
				nl[i]=nr[i]=dpd[vg[x][i].first]+vg[x][i].second;
			}
			for(int i=1; i<=sz-1; ++i) apn(nl[i],nl[i-1]);
			for(int i=sz-2; i>=0; --i) apn(nr[i],nr[i+1]);
			for(int i=0; i<sz; ++i){
				lint vl=i==0?1e14:nl[i-1],vr=i==sz-1?1e14:nr[i+1];
				apn(dpu[vg[x][i].first],std::min(dpu[x],std::min(vl,vr))+vg[x][i].second);
			}
		}
	}
}

namespace T2{
	int cnt,fir[N],cur_sz,cur_rt,cur_xs;
	int cls,sz[N],ls[N];
	lint dep[N];
	bool vis[N];
	struct edge{
		int to,wi,nx;
	}eg[N<<1];

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	void dfs_rt(const int x,const int f){
		sz[x]=1;
		int xsz=0;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==f||vis[y]) continue;
			dfs_rt(y,x);
			apx(xsz,sz[y]);
			sz[x]+=sz[y];
		}
		apx(xsz,cur_sz-sz[x]);
		if(xsz<cur_xs){
			cur_rt=x,cur_xs=xsz;
		}
	}
	void dfs_dep(const int x,const int f){
		ls[++cls]=x;
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==f||vis[y]) continue;
			dep[y]=dep[x]+eg[i].wi;
			dfs_dep(y,x);
			sz[x]+=sz[y];
		}
	}

	int qrt(const int x,const int sz){
		cur_sz=sz,cur_xs=1e9;
		dfs_rt(x,0);
		return cur_rt;
	}

	void dfs_main(int x,const int csz){
		x=qrt(x,csz);
		vis[x]=1;
		cls=dep[x]=0;
		dfs_dep(x,0);
		T1::vmain(ls,cls,dep);
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!vis[y]) dfs_main(y,sz[y]);
		}
	}
}

int main(){
	n=nxi();
	memset(abuk+1,10,n*sizeof(abuk[0]));
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi(),v=nxi();
		T1::add(a,b,v),T1::add(b,a,v);
	}
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi(),v=nxi();
		T2::add(a,b,v),T2::add(b,a,v);
	}
	T1::dfs_son(1);
	T1::dfs_top(1);
	T2::dfs_main(1,n);
	lint ans=0;
	eprintf("abuk: ");
	for(int i=1; i<=n; ++i){
		ans^=abuk[i];
		eprintf("%lld ",abuk[i]);
	}
	eprintf("\n");
	printf("%lld\n",ans);
	return 0;
}
