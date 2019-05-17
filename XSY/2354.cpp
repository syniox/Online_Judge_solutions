#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <queue>
const int N=1005;
int n,m,d,tot;

namespace utils{
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}

	template <class T>
		inline void apx(T &x,const T y){
			x<y?x=y:0;
		}

	template <class T>
		inline void apn(T &x,const T y){
			x>y?x=y:0;
		}
}
using namespace utils;

namespace G{
	int ans,cnt=1,fir[N*3],dis[N*3],pre_e[N*3],pre_p[N*3];
	struct edge{
		int to,wi,cs,nx;
	}eg[(int)2.2e5];
	struct data{
		int x,v;
		friend bool operator < (const data &a,const data &b){
			return a.v>b.v;
		}
	};

	inline void add(const int a,const int b,const int v,const int c){
		//printf("add: %d->%d v%d c%d\n",a,b,v,c);
		eg[++cnt]=(edge){b,v,c,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,0,-c,fir[b]};
		fir[b]=cnt;
	}

	bool dij(){
		static int lstdis[N*3];
		static bool vis[N*3];
		std::priority_queue <data> pq;
		memcpy(lstdis,dis,(tot+2)*sizeof(int));
		memset(vis,0,(tot+2)*sizeof(bool));
		memset(dis,10,(tot+2)*sizeof(int));
		dis[0]=0;
		pq.push((data){0,0});
		while(!pq.empty()){
			data x=pq.top();
			pq.pop();
			if(vis[x.x]) continue;
			vis[x.x]=1;
			for(int i=fir[x.x]; i; i=eg[i].nx){
				if(!eg[i].wi) continue;
				const int y=eg[i].to,v=dis[x.x]+eg[i].cs;
				if(dis[y]>v){
					pre_e[y]=i;
					pre_p[y]=x.x;
					dis[y]=v;
					pq.push((data){y,v-lstdis[y]});
				}
			}
		}
		return dis[tot+1]<1e8;
	}

	bool ncmf(){
		int flow=0;
		while(dij()){
			for(int i=tot+1; i; i=pre_p[i]){
				int e=pre_e[i];
				--eg[e].wi;
				++eg[e^1].wi;
			}
			++flow;
			ans+=dis[tot+1];
		}
		return flow==n;
	}
}

int main(){
	n=nxi(),m=nxi(),d=nxi();
	tot=n+m+d;
	for(int i=1; i<=m; ++i){
		int c=nxi(),s=nxi();
		G::add(s,i+d,1,c);
		for(int j=nxi(); j; --j){
			G::add(i+d,nxi()+d+m,1,0);
		}
	}
	for(int i=1; i<=d; ++i){
		G::add(0,i,nxi(),0);
	}
	for(int i=1; i<=n; ++i){
		G::add(d+m+i,tot+1,1,0);
	}
	printf("%d\n",G::ncmf()?G::ans:-1);
	return 0;
}
