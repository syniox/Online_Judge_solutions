#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1005;
int n,q;

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
	int cnt=1,fir[N<<1],dis[N<<1],pre_p[N<<1],pre_e[N<<1];
	struct edge{
		int to,wi,cs,nx;
	}eg[(int)3e4];

	inline void add(const int a,const int b,const int v,const int c){
		//printf("add: %d - %d v%d c%d\n",a,b,v,c);
		eg[++cnt]=(edge){b,v,c,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,0,-c,fir[b]};
		fir[b]=cnt;
	}

	bool spfa(){
		static int que[N<<1];
		static bool vis[N<<1];
		memset(dis,127,((n+1)<<1)*sizeof(int));
		int hd=0,tl=1;
		que[hd]=0;
		dis[0]=0;
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
		return dis[n<<1|1]<2e9;
	}

	int ncmf(){
		int ans=0;
		while(spfa()){
			int flow=2e9;
			for(int i=n<<1|1; i; i=pre_p[i]){
				apn(flow,eg[pre_e[i]].wi);
			}
			ans+=flow*dis[n<<1|1];
			for(int i=n<<1|1; i; i=pre_p[i]){
				const int e=pre_e[i];
				eg[e].wi-=flow;
				eg[e^1].wi+=flow;
			}
		}
		for(int i=fir[0]; i; i=eg[i].nx){
			assert(eg[i].wi==0);
		}
		return ans;
	}
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		const int v=nxi();
		G::add(0,i+n,v,0);
		G::add(i,n<<1|1,v,0);
		G::add(i,i+n,2e9,0);
		if(i<n){
			G::add(i+n,i+1,2e9,0);
		}
	}
	for(int i=1; i<=q; ++i){
		const int a=nxi(),b=nxi(),v=nxi();
		assert(a<=b);
		G::add(b+n,a,2e9,v);
	}
	printf("%d\n",G::ncmf());
	return 0;
}
