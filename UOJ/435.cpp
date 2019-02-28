#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
const int N=1e5+5;
const int S=320;
int n,q;
int val[N],bel[N];//dfn
int dfn[N],idx[N];
bool type;


inline char get_c(){
	static char *h,*t,buf[20000];
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while(((c=get_c())>'9'||c<'0')&&c!='-');
	const bool f=c=='-'&&(c=get_c());
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return f?-x:x;
}

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline bool cmp_val(const int a,const int b){
	return val[a]<val[b];
}

namespace T{
	int tr[N];

	inline void mod(int x,const int v){
		for(; x<N; x+=x&-x) tr[x]+=v;
	}
	inline int ask(int x){
		int ans=0;
		for(; x; x-=x&-x) ans+=tr[x];
		return ans;
	}
	inline int ask(const int x,const int y){
		if(x>y) return 0;
		return ask(y)-ask(x-1);
	}
}

int ask_cnt,mod_cnt;

namespace B{
	int tag[N];
	int cnb,*blk[N],blk_l[N],blk_r[N],blk_sz[N];
	int sum_blk[N];

	inline bool positive(const int x){//dfn
		return val[x]+tag[bel[x]]>0;
	}

	inline int ask_blk(const int p){
		int l=0,r=blk_sz[p],mid;
		while(l!=r){
			mid=(l+r)>>1;
			if(val[blk[p][mid]]+tag[p]>0) r=mid;
			else l=mid+1;
		}
		return blk_sz[p]-l;
	}

	inline void upd_blk(const int p){
		int presum=sum_blk[p];
		sum_blk[p]=ask_blk(p);
		T::mod(p,sum_blk[p]-presum);
	}

	inline void build_blk(const int p){
		int pt=0;
		for(int i=blk_l[p]; i<=blk_r[p]; ++i){
			blk[p][pt++]=i;
		}
		std::sort(blk[p],blk[p]+pt,cmp_val);
		upd_blk(p);
	}

	inline void new_blk(const int l,const int r){
		blk[++cnb]=new int[r-l+1];
		blk_sz[cnb]=r-l+1;
		blk_l[cnb]=l,blk_r[cnb]=r;
		for(int i=l; i<=r; ++i){
			bel[i]=cnb;
		}
		build_blk(cnb);
	}

	inline void mod_blk(const int p,const int delta){
		tag[p]+=delta;
		upd_blk(p);
	}

	inline int ask(int l,int r){
		assert(bel[l]==bel[r]);
		if(l>r) std::swap(l,r);
		if(r-l+1==blk_sz[bel[l]]) return sum_blk[bel[l]];
		int ans=0;
		for(int i=l; i<=r; ++i){
			if(val[i]+tag[bel[l]]>0) ++ans;
		}
		return ans;
	}

	inline void mod(int l,int r,const int v){
		static int buk1[N],buk2[N];
		assert(bel[l]==bel[r]);
		if(l>r) std::swap(l,r);
		const int p=bel[l];
		if(r-l+1==blk_sz[p]){
			mod_blk(bel[l],v);
			return;
		}
		int pt1=0,pt2=0,pt=0;
		for(int i=l; i<=r; ++i){
			val[i]+=v;
		}
		for(int i=0; i<blk_sz[p]; ++i){
			if(blk[p][i]>=l&&blk[p][i]<=r) buk1[pt1++]=blk[p][i];
			else buk2[pt2++]=blk[p][i];
		}
		for(int i=0,j=0; i<=pt1&&j<=pt2;){
			if(i==pt1){
				while(j<pt2) blk[p][pt++]=buk2[j++];
			}
			if(j==pt2){
				while(i<pt1) blk[p][pt++]=buk1[i++];
			}
			blk[p][pt++]=val[buk1[i]]<val[buk2[j]]?buk1[i++]:buk2[j++];
		}
		upd_blk(p);
	}
}

namespace G{
	int cnt,fir[N],fa[N],dep[N],mx_blk[N];
	int sz[N],son[N],top[N],bot[N];
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
		static int cnd;
		dfn[x]=++cnd;
		idx[cnd]=x;
		top[x]=son[fa[x]]==x&&dep[x]-dep[top[fa[x]]]<S?top[fa[x]]:x;
		bot[top[x]]=x;
		if(son[x]) dfs_top(son[x]);
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!dfn[y]) dfs_top(y);
		}
	}

	void dfs_blk(const int x){
		if(top[x]==x){
			B::new_blk(dfn[x],dfn[bot[x]]);
		}
		bot[x]=bot[top[x]];
		mx_blk[x]=bel[dfn[x]];
		if(son[x]) dfs_blk(son[x]);
		apx(mx_blk[x],mx_blk[son[x]]);
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa[x]&&y!=son[x]){
				dfs_blk(y);
				apx(mx_blk[x],mx_blk[y]);
			}
		}
	}

	inline int get_lca(int x,int y){
		while(top[x]!=top[y]){
			dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]];
		}
		return dep[x]<dep[y]?x:y;
	}

	inline void mod(int x,int y,int v){
		while(top[x]!=top[y]){
			if(dep[top[x]]>dep[top[y]]){
				B::mod(dfn[top[x]],dfn[x],v);
				x=fa[top[x]];
			}
			else{
				B::mod(dfn[top[y]],dfn[y],v);
				y=fa[top[y]];
			}
		}
		if(dep[x]>dep[y]) std::swap(x,y);
		B::mod(dfn[x],dfn[y],v);
	}

	inline int ask_ln(int x,int y){
		int ans=0;
		while(top[x]!=top[y]){
			if(dep[top[x]]>dep[top[y]]){
				ans+=B::ask(dfn[top[x]],dfn[x]);
				x=fa[top[x]];
			}
			else{
				ans+=B::ask(dfn[top[y]],dfn[y]);
				y=fa[top[y]];
			}
		}
		if(dep[x]>dep[y]) std::swap(x,y);
		return ans+B::ask(dfn[x],dfn[y]);
	}

	inline int ask_st(const int x){
		int ans=B::ask(dfn[x],dfn[bot[x]]);
		return ans+T::ask(bel[dfn[x]]+1,mx_blk[x]);
	}
}

int main(){
	n=nxi(),q=nxi(),type=nxi();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	G::dfs_son(1);
	G::dfs_top(1);
	for(int i=1; i<=n; ++i){
		val[dfn[i]]=nxi();
	}
	G::dfs_blk(1);
	for(int ans=0; q; --q){
		using G::dep;
		int op=nxi(),x,y,w;
		switch(op){
			case 1:
				x=nxi(),y=nxi(),w=nxi();
				if(type) x^=ans,y^=ans;
				if(dep[x]>dep[y]) std::swap(x,y);
				G::mod(x,y,w);
				break;
			case 2:
				x=nxi(),y=nxi();
				if(type) x^=ans,y^=ans;
				if(dep[x]>dep[y]) std::swap(x,y);
				printf("%d\n",ans=G::ask_ln(x,y));
				break;
			case 3:
				x=nxi();
				if(type) x^=ans;
				printf("%d\n",ans=G::ask_st(x));
				break;
		}
	}
	return 0;
}
