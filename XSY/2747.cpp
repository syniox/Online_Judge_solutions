#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=105;
const int M=505;
int n,m,q,lim;
struct edge{
	int x,y,v;
}eg[M];
struct _pair{
	int x,y;
}qry[N];

template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

inline int nxi(FILE *fd=stdin){
	int x=0;
	char c;
	while((c=fgetc(fd))>'9'||c<'0');
	while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
	return x;
}

namespace G{
	int cnt,fir[N],odgr[N],fr_e[N],fr_p[N];
	lint ans,dis[N];
	struct edge{
		int to,wi,nx;
		lint cs;
	}eg[(N+M)*4];

	inline void clear(){
		cnt=1,ans=0;
		memset(fir,0,(n+2)*sizeof(int));
		memset(odgr+1,0,n*sizeof(int));
	}

	inline void add(int a,int b,const int v,lint c){
		//printf("add: %d -> %d: v%d,c%lld\n",a,b,v,c);
		if(c>0){
			odgr[a]+=v,odgr[b]-=v;
			c=-c;
			std::swap(a,b);
		}
		eg[++cnt]=(edge){b,v,fir[a],c};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,0,fir[b],-c};
		fir[b]=cnt;
	}

	bool spfa(){
		static int que[N];
		static bool vis[N];
		for(int i=1; i<=n+1; ++i){
			dis[i]=-1e18;
		}
		dis[0]=0;
		int hd=0,tl=1;
		que[0]=0;
		while(hd!=tl){
			const int x=que[hd++];
			if(hd==N) hd=0;
			vis[x]=0;
			for(int i=fir[x]; i; i=eg[i].nx){
				if(!eg[i].wi) continue;
				const int y=eg[i].to;
				const lint v=dis[x]+eg[i].cs;
				if(v>dis[y]){
					fr_e[y]=i,fr_p[y]=x;
					dis[y]=v;
					if(!vis[y]){
						que[tl++]=y;
						if(tl==N) tl=0;
						vis[y]=1;
					}
				}
			}
		}
		return dis[n+1]>-1e18;
	}

	int jdg(const int tgt){
		clear();
		for(int i=1; i<=m; ++i){
			const int x=::eg[i].x,y=::eg[i].y;
			ans+=::eg[i].v*1e4;
			G::add(x,y,1,::eg[i].v*1e4);
			G::add(x,y,1e9,0);
		}
		for(int i=1; i<=n; ++i){
			if(odgr[i]>0){
				G::add(i,n+1,odgr[i],0);
			}
			else if(odgr[i]<0){
				G::add(0,i,-odgr[i],0);
			}
		}
		for(int i=1; i<=q; ++i){
			G::add(qry[i].y,qry[i].x,1,tgt*1e3-1);
		}
		while(spfa()){
			int flow=1e9;
			for(int i=n+1; i; i=fr_p[i]){
				int e=fr_e[i];
				apn(flow,eg[e].wi);
			}
			assert(flow);
			for(int i=n+1; i; i=fr_p[i]){
				int e=fr_e[i];
				eg[e].wi-=flow;
				eg[e^1].wi+=flow;
			}
			ans+=(lint)flow*dis[n+1];
		}
		for(int i=fir[0]; i; i=eg[i].nx){
			if(eg[i].wi) return 0;
		}
		for(int i=fir[n+1]; i; i=eg[i].nx){
			if(eg[i^1].wi) return 0;
		}
		return ((int)1e3-(ans%(int)1e3))%(int)1e3;
	}
}

double solve(){
	//最大费用时的最大循环流（最少边）
	int l=-2e5,r=0,mid;
	while(l!=r){
		mid=(l+r)>>1;
		if(G::jdg(mid)<lim) l=mid+1;
		else r=mid;
	}
	G::jdg(l);
	return (G::ans-1e3*lim*l)/1e4;
}

int main(){
	n=nxi(),m=nxi(),q=nxi(),lim=nxi();
	for(int i=1; i<=m; ++i){
		eg[i].x=nxi(),eg[i].y=nxi();
		eg[i].v=nxi();
	}
	for(int i=1; i<=q; ++i){
		qry[i].x=nxi(),qry[i].y=nxi();
	}
	//G::jdg(0);
	printf("%.0lf\n",solve());
	return 0;
}
