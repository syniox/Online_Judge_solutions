#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N=1e5+5;
int n,q;

template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}
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
	int rt,cnt,fir[N],rad_l,low_pt[N],jmp[18][N];
	int dep[N],son[N],fa[N],dis_to_fa[N],xdep[N],top[N],bot[N];
	int dfn[N],idx[N];
	int cnt_lf,lf[N<<1],rnk_lf[N<<1],pre_lf[N<<1];//lf->leaf
	struct edge{
		int to,wi,nx;
	}eg[N<<1];

	inline bool cmp_len(const int a,const int b){
		return dep[a]-dep[fa[top[a]]]>dep[b]-dep[fa[top[b]]];
	}

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	int dfs_rt(const int x,const int fa){
		low_pt[x]=x;
		int xlen=0;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa) continue;
			dis_to_fa[y]=eg[i].wi;
			int ylen=dfs_rt(y,x)+eg[i].wi;
			if(xlen+ylen>rad_l){
				rad_l=xlen+ylen;
				rt=low_pt[x];
			}
			if(xlen<ylen){
				low_pt[x]=low_pt[y];
				xlen=ylen;
			}
		}
		return xlen;
	}

	void dfs_son(const int x){
		xdep[x]=dep[x];
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa[x]) continue;
			fa[y]=x;
			dep[y]=dep[x]+eg[i].wi;
			dfs_son(y);
			if(xdep[y]>xdep[x]){
				xdep[x]=xdep[y],son[x]=y;
			}
		}
	}

	void dfs_top(const int x){
		static int cnd;
		dfn[x]=++cnd;
		idx[cnd]=x;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		bot[top[x]]=x;
		if(son[x]) dfs_top(son[x]);
		else lf[++cnt_lf]=x;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!top[y]) dfs_top(y);
		}
	}

	inline void build(){
		std::sort(lf+1,lf+cnt_lf+1,cmp_len);
		for(int i=1; i<=n; ++i){
			bot[i]=bot[top[i]];
			jmp[0][i]=fa[i];
		}
		for(int i=1; i<18; ++i){
			for(int j=1; j<=n; ++j){
				jmp[i][j]=jmp[i-1][jmp[i-1][j]];
			}
		}
		for(int i=1; i<=cnt_lf; ++i){
			rnk_lf[lf[i]]=i;
			pre_lf[i]=pre_lf[i-1]+dep[lf[i]]-dep[fa[top[lf[i]]]];
		}
	}

	inline int to_painted(int x,const int limit){
		for(int i=17; ~i; --i){
			if(rnk_lf[bot[jmp[i][x]]]>limit){
				x=jmp[i][x];
			}
		}
		return fa[x];
	}
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi(),v=nxi();
		G::add(a,b,v);
		G::add(b,a,v);
	}
	G::dfs_rt(1,0);
	G::dfs_son(G::rt);
	G::dfs_top(G::rt);
	G::build();
	for(int ans=0,i=1; i<=q; ++i){
		const int x=((nxi()+ans)-1)%n+1;
		const int y=((nxi()+ans)-1)%n+1;
		int organs=G::pre_lf[std::min(G::cnt_lf,(y<<1)-1)];
		if(G::rnk_lf[G::bot[x]]<=(y<<1)-1) printf("%d\n",ans=organs);
		else{
			using G::dep;
			using G::bot;
			using G::top;
			int res=0,up=G::to_painted(x,(y<<1)-1);
			apx(res,organs-dep[up]);
			apx(res,organs-(dep[bot[up]]-dep[up]));
			apx(res,organs-(dep[G::lf[(y<<1)-1]]-dep[G::fa[top[G::lf[(y<<1)-1]]]]));
			printf("%d\n",ans=(res+dep[bot[x]]-dep[up]));
		}
	}
	return 0;
}
