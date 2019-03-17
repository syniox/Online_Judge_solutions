#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cassert>
const int N=1e5+5;
int n;

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}
template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace T{
	int cnt,tot_sz,cur_id,mx_id,rt[N];
	int x,y,v;
	bool type;
	class _Node{
		public:
			int ls,rs,v;
	}tr[35000000];

	inline void upd(const int k){
		tr[k].v=tr[tr[k].ls].v+tr[tr[k].rs].v;
	}

	inline int get_sp(const int len){
		int tmp=tot_sz+1;
		tot_sz+=len;
		return tmp;
	}

	inline int ask_t(const int k,const int l,const int r){
		if(!k||!tr[k].v) return 1e9;
		if(l==r) return l;
		const int mid=(l+r)>>1;
		int ans=1e9;
		if(x<=mid&&tr[tr[k].ls].v) ans=ask_t(tr[k].ls,l,mid);
		if(ans<1e9) return ans;
		if(y>mid&&tr[tr[k].rs].v) ans=ask_t(tr[k].rs,mid+1,r);
		return ans;
	}

	void mod_t(const int k,int &p,const int l,const int r){
		p=++cnt;
		tr[p]=tr[k];
		if(l==r){
			tr[p].v+=v;
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_t(tr[k].ls,tr[p].ls,l,mid);
		else mod_t(tr[k].rs,tr[p].rs,mid+1,r);
		upd(p);
	}

	inline int ask(const int k,const int l,const int r){
		T::x=l,T::y=r;
		int res=ask_t(rt[k],1,tot_sz);
		return res==1e9?1e9:res-l;
	}

	inline void mod(const int x,const int v,const bool type){
		T::x=x,T::v=v;
		if(!type) mod_t(rt[cur_id],rt[cur_id],1,tot_sz);
		else{
			++mx_id;
			mod_t(rt[cur_id],rt[mx_id],1,tot_sz);
			cur_id=mx_id;
		}
	}
}

namespace G{
	int cnt,fir[N];
	int cur_rt,tot_sz,sz[N],stp[N],xdep[N];
	int dis_fa[N][20],fa[N][20],cnt_f[N];
	bool vis[N];
	class edge{
		public:
			int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs_rt(const int x,const int fa){
		static int xsz[N];
		sz[x]=1,xsz[x]=0;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(vis[y]||y==fa) continue;
			dfs_rt(y,x);
			sz[x]+=sz[y];
			apx(xsz[x],sz[y]);
		}
		apx(xsz[x],tot_sz-xsz[x]);
		if(!cur_rt||xsz[x]<xsz[cur_rt]) cur_rt=x;
	}

	int dfs_xdep(const int x,const int fa){
		int xdep=0;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!vis[y]&&y!=fa){
				dis_fa[y][++cnt_f[y]]=dis_fa[x][cnt_f[x]]+1;
				G::fa[y][cnt_f[y]]=cur_rt;
				apx(xdep,dfs_xdep(y,x)+1);
			}
		}
		return xdep;
	}

	inline int get_rt(const int x,const int tot_sz){
		G::tot_sz=tot_sz;
		cur_rt=0,dfs_rt(x,0);
		return cur_rt;
	}

	inline void split(int x,int tot_sz){
		vis[x]=1;
		int pt=0;
		dis_fa[x][++cnt_f[x]]=0;
		fa[x][cnt_f[x]]=x;
		xdep[x]=dfs_xdep(x,0);
		assert(cur_rt==x);
		stp[x]=T::get_sp(xdep[x]+1);
		for(int i=fir[x]; i; ++pt,i=eg[i].nx){
			if(vis[eg[i].to]) continue;
			int y=get_rt(eg[i].to,sz[eg[i].to]);
			split(y,sz[eg[i].to]);
		}
	}

	inline void mod(const int x){
		bool type=T::ask(T::cur_id,stp[x],stp[x]);//type==0: delete
		for(int i=1; i<=cnt_f[x]; ++i){
			const int f=fa[x][i];
			T::mod(stp[f]+dis_fa[x][i],type==1?1:-1,i==1);
		}
	}

	inline int ask(const int x){
		int ans=1e9;
		for(int i=1; i<=cnt_f[x]; ++i){
			const int f=fa[x][i];
			apn(ans,dis_fa[x][i]+T::ask(T::cur_id,stp[f],stp[f]+xdep[f]));
		}
		return ans;
	}
}

int main(){
	n=nxi();
	for(int i=1; i<n; ++i){
		const int x=nxi(),y=nxi();
		G::add(x,y);
		G::add(y,x);
	}
	G::split(G::get_rt(1,n),n);
	for(int ans=0,q=nxi(); q; --q){
		const int op=nxi(),x=nxi()^ans;
		switch(op){
			case 1:
				G::mod(x);
				break;
			case 2:
				printf("%d\n",ans=G::ask(x));
				break;
			case 3:
				T::cur_id=x;
				break;
		}
	}
	return 0;
}
