#include <iostream>
#include <cstdio>
#include <cstring>
const int N=505;
int n,m,q;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,fir[N],dis[N],que[N],cq[N];
	bool vis[N];
	struct edge{
		int to,wi,nx;
	}eg[N*N<<2];

	inline void init(){
		cnt=0;
		memset(fir,0,sizeof(fir));
		memset(cq,0,sizeof(cq));
		memset(vis,0,sizeof(vis));
	}

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	inline bool spfa(){
		memset(dis,31,sizeof(dis));
		int hd=0,tl=1;
		que[0]=1;
		dis[1]=0;
		while(hd!=tl){
			const int x=que[hd++];
			if(hd==N) hd=0;
			vis[x]=0;
//			printf("%d: %d\n",x,dis[x]);
			for(int i=fir[x];i;i=eg[i].nx){
				const int y=eg[i].to;
				if(dis[y]>dis[x]+eg[i].wi){
					if(++cq[y]>n) return 1;
					dis[y]=dis[x]+eg[i].wi;
					if(!vis[y]){
						vis[y]=1;
						que[tl++]=y;
						if(tl==N) tl=0;
					}
				}
			}
		}
		return 0;
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	int T=nxi();
	while(T--){
		n=nxi(),m=nxi(),q=nxi();
		G::init();
		for(int i=1;i<=m;++i){
			const int x=nxi(),y=nxi(),v=nxi();
			G::add(x,y,v);
			G::add(y,x,v);
		}
		for(int i=1;i<=q;++i){
			const int x=nxi(),y=nxi(),v=nxi();
			G::add(x,y,-v);
		}
		puts(G::spfa()?"YES":"NO");
	}
	return 0;
}
