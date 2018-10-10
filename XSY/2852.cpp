#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1002;
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

inline void xswp(int &x,int &y){
	if(x<y) std::swap(x,y);
}

namespace G{
	int rt,xsz,cnt,sz[N],fa[N],fir[N];
	bool vis[N];
	struct edge{
		int to,nx;
	}eg[N<<1];
	inline void init(){
		cnt=0;
		memset(fir,0,sizeof(fir));
		memset(sz,0,sizeof(sz));
		memset(vis,0,sizeof(vis));
	}
	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}
	void init(const int x){
		sz[x]=1;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa[x]){
				fa[y]=x;
				init(y);
				sz[x]+=sz[y];
			}
		}
	}
	void get_rt(const int x){
		vis[x]=1;
		int xsz=0;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!vis[y]){
				get_rt(y);
				apx(xsz,sz[y]);
			}
		}
		apx(xsz,n-sz[x]);
		if(xsz>G::xsz){
			rt=x;
			G::xsz=xsz;
		}
	}
	bool dfs(const int x,const int fa){
		sz[x]=1;
		int xsz1=0,xsz2=0;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa){
				if(!dfs(y,x)) return 0;
				sz[x]+=sz[y];
				int tp=sz[y];
				xswp(xsz1,tp);
				xswp(xsz2,tp);
			}
		}
		return xsz1<=xsz2+1;
	}
}

int main(){
	int T=nxi();
	n=nxi();
	while(T--){
		G::init();
		for(int i=1;i<n;++i){
			const int x=nxi(),y=nxi();
			G::add(x,y);
			G::add(y,x);
		}
		G::xsz=1e8;
		G::init(1);
		G::get_rt(1);
		puts(G::dfs(G::rt,0)?"Yes":"No");
	}
	return 0;
}
