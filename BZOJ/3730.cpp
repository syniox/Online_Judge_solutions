#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

const int N=1e5+2;
int n,m,val[N],dis[N][20];
//dis: opposite meaning of LCA.count points.

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline char get_c(){
	static char *h,*t,buf[200000];
	if(h==t){
		t=(h=buf)+fread(buf,1,200000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace B{
	int pt;
	int mpool[N*18*2];
	struct node{
		int sz,*sum;
		inline void mod(int x,const int v){
			for(;x<=sz;x+=x&-x) sum[x]+=v;
		}
		inline int ask(int x){
			if(x<0) return 0;
			apn(x,sz);
			int ans=0;
			for(;x;x-=x&-x) ans+=sum[x];
			return ans;
		}
	}tr[N],ftr[N];

	inline void getsize(node &x,const int size){
		x=(node){size,mpool+pt};
		pt+=size+1;
	}
}

namespace G{
	int cnt,fir[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}
}

namespace T{
	int buk[N],dep[N],xdep[N],f_dep[N];
	int rt,cur_size,link[N],sz[N],xson[N];
	bool vis[N];
	std::vector <int> edge_to[N];

	inline void init(){
		xson[0]=1e9;
	}

	void dfs_root(const int x,const int fa){
		sz[x]=1;
		xson[x]=0;
		for(int i=G::fir[x];i;i=G::eg[i].nx){
			const int y=G::eg[i].to;
			if(y!=fa&&!vis[y]){
				dfs_root(y,x);
				sz[x]+=sz[y];
				apx(xson[x],sz[y]);
			}
		}
		apx(xson[x],cur_size-sz[x]);
		if(xson[x]<xson[rt]) rt=x;
	}

	inline void get_dep(const int x,const int fa){
		xdep[x]=dep[x];
		buk[dep[x]]+=val[x];
		sz[x]=1;
		for(int i=G::fir[x];i;i=G::eg[i].nx){
			const int y=G::eg[i].to;
			if(y!=fa&&!vis[y]){
				dep[y]=dep[x]+1;
				dis[y][++f_dep[y]]=dep[y];
				get_dep(y,x);
				sz[x]+=sz[y];
				apx(xdep[x],xdep[y]);
			}
		}
	}

	inline void get_ftr(const int x,const int fa){
		buk[dep[x]]+=val[x];
		xdep[x]=dep[x];
		for(int i=G::fir[x];i;i=G::eg[i].nx){
			const int y=G::eg[i].to;
			if(y!=fa&&!vis[y]){
				dep[y]=dep[x]+1;
				get_ftr(y,x);
				apx(xdep[x],xdep[y]);
			}
		}
	}

	inline int get_root(const int x,const int size){
		T::rt=0,T::cur_size=size;
		dfs_root(x,0);
		return rt;
	}

	void build(int x){
		using G::fir;
		using G::eg;
		vis[x]=1;
		dep[x]=1;
		get_dep(x,0);
		B::getsize(B::tr[x],xdep[x]);
		for(int i=1;i<=xdep[x];++i){
			B::tr[x].mod(i,buk[i]);
		}
		memset(buk,0,(xdep[x]+1)<<2);

		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!vis[y]){
				const int rt_y=get_root(y,sz[y]);
				edge_to[x].push_back(rt_y);
				link[rt_y]=x;
				dep[y]=2;
				get_ftr(y,x);
				B::getsize(B::ftr[rt_y],xdep[y]);
				for(int i=1;i<=xdep[y];++i){
					if(buk[i]){
						B::ftr[rt_y].mod(i,buk[i]);
					}
				}
				memset(buk,0,(xdep[y]+1)<<2);
			}
		}
		const int limit=edge_to[x].size();
		for(int i=0;i<limit;++i){
			build(edge_to[x][i]);
		}
	}

	inline void mod(const int x,const int v){
		B::tr[x].mod(1,v);
		for(int i=f_dep[x],f=x;i;--i,f=link[f]){
			B::ftr[f].mod(dis[x][i],v);
			B::tr[link[f]].mod(dis[x][i],v);
		}
	}

	inline int ask(const int x,const int xdis){
		int ans=B::tr[x].ask(xdis+1);
		for(int i=f_dep[x],f=x;i;--i,f=link[f]){
			ans-=B::ftr[f].ask((xdis+1)-dis[x][i]+1);
			ans+=B::tr[link[f]].ask((xdis+1)-dis[x][i]+1);
		}
		return ans;
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("c.in","r",stdin);
#endif //ONLINE_JUDGE

	n=nxi(),m=nxi();
	for(int i=1;i<=n;++i){
		val[i]=nxi();
	}
	for(int i=1;i<n;++i){
		const int x=nxi(),y=nxi();
		G::add(x,y);
		G::add(y,x);
	}
	T::init();
	T::build(T::get_root(1,n));
	for(int i=1,ans=0;i<=m;++i){
		const int op=nxi(),x=nxi()^ans,y=nxi()^ans;
		if(op==0) printf("%d\n",ans=T::ask(x,y));
		else if(val[x]!=y){
			T::mod(x,y-val[x]);
			val[x]=y;
		}
	}
	return 0;
}
