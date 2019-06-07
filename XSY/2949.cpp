#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1005;
int n,q,lim_s,lim_e,val[N];
//先假设全部睡觉，k天吃饭限制: [lim_e,q-lim_s]

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
	int cnt=1,fir[N],pre_e[N],pre_p[N];
	lint dis[N];
	struct edge{
		int to,wi,cs,nx;
	}eg[N<<2];

	inline void add(const int a,const int b,const int v,const int c){
		//printf("add: %d-%d v%d c%d\n",a,b,v,c);
		eg[++cnt]=(edge){b,v,c,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,0,-c,fir[b]};
		fir[b]=cnt;
	}

	bool spfa(){
		static int que[N];
		static bool vis[N];
		memset(dis,-10,(n+2)*sizeof(dis[0]));
		int hd=0,tl=1;
		que[0]=0;
		dis[0]=0;
		while(hd!=tl){
			const int x=que[hd++];
			if(hd==N) hd=0;
			vis[x]=0;
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				const lint v=dis[x]+eg[i].cs;
				if(eg[i].wi&&dis[y]<v){
					pre_p[y]=x;
					pre_e[y]=i;
					dis[y]=v;
					if(!vis[y]){
						que[tl++]=y;
						if(tl==N) tl=0;
						vis[y]=1;
					}
				}
			}
		}
		return dis[n+1]>-1e15;
	}

	lint mcmf(){
		lint ans=0;
		while(spfa()){
			int flow=1e9;
			for(int i=n+1; i; i=pre_p[i]){
				apn(flow,eg[pre_e[i]].wi);
			}
			ans+=dis[n+1]*flow;
			for(int i=n+1; i; i=pre_p[i]){
				const int e=pre_e[i];
				eg[e].wi-=flow;
				eg[e^1].wi+=flow;
			}
		}
		return ans;
	}
}

int main(){
	n=nxi(),q=nxi(),lim_s=nxi(),lim_e=nxi();
	lint ans=0;
	for(int i=1; i<=n; ++i){
		ans+=(val[i]=nxi());
	}
	for(int i=1; i<=n; ++i){
		G::add(i,std::min(n+1,i+q),1,nxi()-val[i]);
	}
	for(int i=1; i<=q; ++i){
		G::add(i-1,i,q-lim_s,0);
	}
	for(int i=q+1; i<=n+1; ++i){
		G::add(i-1,i,q-lim_s-lim_e,0);
	}
	ans+=G::mcmf();
	printf("%lld\n",ans);
	return 0;
}
