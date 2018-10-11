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
	int rt[2],cnr,xsz,cnt,sz[N],fa[N],fir[N];
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
	void get_rt(const int x){
		sz[x]=1;
		int xsz=0;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!sz[y]){
				get_rt(y);
				sz[x]+=sz[y];
				apx(xsz,sz[y]);
			}
		}
		apx(xsz,n-sz[x]);
		if((xsz<<1)<=n) rt[cnr++]=x;
	}
	bool dfs(const int x,const int fa){
		sz[x]=1;
		int xsz=0;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa){
				if(!dfs(y,x)) return 0;
				sz[x]+=sz[y];
				apx(xsz,sz[y]);
			}
		}
		return xsz<=sz[x]-xsz+1;
	}
}

inline bool jdg(){
	bool f=0;
	f|=G::dfs(G::rt[0],0);
	if(!f&&G::cnr>1) f|=G::dfs(G::rt[1],0);
	return f;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("c.in","r",stdin);
#endif
	int T=nxi();
	n=nxi();
	while(T--){
		G::init();
		for(int i=1;i<n;++i){
			const int x=nxi(),y=nxi();
			G::add(x,y);
			G::add(y,x);
		}
		G::cnr=0;
		G::get_rt(1);
		puts(jdg()?"Yes":"No");
	}
	return 0;
}
