#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=52;
int n;

namespace utils{
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

namespace G{
	int cnt,fir[N<<1],dis[N<<1],pre_e[N<<1],pre_p[N<<1];
	struct edge{
		int to,wi,cs,nx;
	}eg[N*N<<2];

	inline void clear(){
		cnt=1;
		memset(fir,0,sizeof(fir));
	}

	inline void add(const int a,const int b,const int v,const int c){
		//printf("add: %d-%d v%d c%d\n",a,b,v,c);
		eg[++cnt]=(edge){b,v,c,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,0,-c,fir[b]};
		fir[b]=cnt;
		assert(cnt<N*N<<2);
	}

	bool spfa(){
		static int que[N<<1];
		static bool vis[N<<1];
		memset(dis,10,sizeof(dis));
		int hd=0,tl=1;
		dis[0]=0;
		que[0]=0;
		while(hd!=tl){
			const int x=que[hd++];
			if(hd==N<<1) hd=0;
			vis[x]=0;
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to,v=dis[x]+eg[i].cs;
				if(eg[i].wi&&dis[y]>v){
					pre_e[y]=i;
					pre_p[y]=x;
					dis[y]=v;
					if(!vis[y]){
						que[tl++]=y;
						if(tl==N<<1) tl=0;
						vis[y]=1;
					}
				}
			}
		}
		return dis[n<<1|1]<1e8;
	}

	int ncmf(){
		int ans=0;
		while(spfa()){
			int flow=1e6;
			for(int i=n<<1|1; i; i=pre_p[i]){
				apn(flow,eg[pre_e[i]].wi);
			}
			assert(flow);
			ans+=dis[n<<1|1]*flow;
			for(int i=n<<1|1; i; i=pre_p[i]){
				const int e=pre_e[i];
				eg[e].wi-=flow;
				eg[e^1].wi+=flow;
			}
		}
		for(int i=fir[0]; i; i=eg[i].nx){
			if(eg[i].wi) return -1;
		}
		return ans;
	}
}

int main(){
	for(int cast=nxi(),cas=1; cas<=cast; ++cas){
		n=nxi();
		const int qc=nxi(),qr=nxi();
		G::clear();
		for(int i=1; i<=n; ++i){
			const int v=nxi();
			G::add(0,i+n,v,0);
			G::add(i,n<<1|1,v,0);
			G::add(i,i+n,1e6,0);
			if(i<n){
				G::add(i,i+1,1e6,0);
				G::add(i+n,i+n+1,1e6,0);
			}
		}
		for(int i=1; i<=qc; ++i){
			const int w=nxi(),v=nxi();
			G::add(n<<1,1,w,v);
		}
		for(int i=1; i<=qr; ++i){
			const int d=nxi(),v=nxi();
			for(int i=1; i<=n-d-1; ++i){
				G::add(i+n,i+d+1,1e6,v);
			}
		}
		int res=G::ncmf();
		printf("Case %d: ",cas);
		if(res==-1) puts("impossible");
		else printf("%d\n",res);
	}
	return 0;
}
