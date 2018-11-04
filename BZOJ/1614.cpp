#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
const int N=1005;
int n,m,q,e_x[N*10],e_y[N*10],e_v[N*10];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,fir[N],dis[N];
	bool vis[N];
	struct edge{
		int to,wi,nx;
	}eg[N*20];
	struct pnt{
		int x,dis;
		bool operator < (const pnt &b) const {
			return dis>b.dis;
		}
	};

	inline void init(){
		cnt=0;
		memset(fir,0,sizeof(fir));
	}

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,v,fir[b]};
		fir[b]=cnt;
	}

	inline void dij(){
		std::priority_queue <pnt> pq;
		memset(dis,1,sizeof(dis));
		memset(vis,0,sizeof(vis));
		pq.push((pnt){1,0});
		dis[1]=0;
		while(!pq.empty()){
			const int x=pq.top().x;
			pq.pop();
			if(vis[x]) continue;
			if(x==n) break;
			vis[x]=1;
			for(int i=fir[x];i;i=eg[i].nx){
				const int y=eg[i].to;
				if(dis[y]>dis[x]+eg[i].wi){
					dis[y]=dis[x]+eg[i].wi;
					pq.push((pnt){y,dis[y]});
				}
			}
		}
	}

	inline bool jdg(const int ddl){
		init();
		for(int i=1;i<=m;++i){
			add(e_x[i],e_y[i],e_v[i]>ddl);
		}
		G::dij();
		return dis[n]<=q;
	}
}

inline int solve(){
	int l=0,r=2e6,mid;
	while(l!=r){
		mid=(l+r)>>1;
		if(G::jdg(mid)) r=mid;
		else l=mid+1;
	}
	return l==2e6?-1:l;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1;i<=m;++i){
		e_x[i]=nxi(),e_y[i]=nxi(),e_v[i]=nxi();
	}
	G::dij();
	printf("%d\n",solve());
	return 0;
}
