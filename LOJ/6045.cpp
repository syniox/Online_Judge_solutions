#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
typedef long long lint;
const int N=305;
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

namespace G0{
	int cnt,fir[N<<1],lnk[N<<1];
	bool vis[N<<1];
	struct edge{
		int to,nx;
	}eg[N*N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,fir[b]};
		fir[b]=cnt;
	}

	bool dfs(const int x){
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(vis[y]) continue;
			vis[y]=1;
			if(lnk[y]&&!dfs(lnk[y])) continue;
			lnk[y]=x,lnk[x]=y;
			return 1;
		}
		return 0;
	}

	void get_lnk(){
		for(int i=1; i<=n; ++i){
			if(!lnk[i]){
				memset(vis+1,0,(n*2)*sizeof(bool));
				dfs(i);
			}
		}
	}
}

namespace G1{
	int cnt=1,fir[N],dep[N],cur[N];
	struct edge{
		int to;
		lint wi;
		int nx;
	}eg[(N*N+N)<<1];

	inline void add(const int a,const int b,const lint v){
		//printf("add: %d -> %d v%d\n",a,b,v);
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,0,fir[b]};
		fir[b]=cnt;
	}

	bool bfs(){
		static int que[N];
		memset(dep,0,(n+2)*sizeof(int));
		int hd=0,tl=1;
		que[0]=0;
		dep[0]=1;
		while(hd!=tl){
			const int x=que[hd++];
			for(int i=cur[x]=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(eg[i].wi&&!dep[y]){
					que[tl++]=y;
					dep[y]=dep[x]+1;
				}
			}
		}
		return dep[n+1];
	}

	lint dfs(const int x,const lint t){
		if(x==n+1) return t;
		lint tt=t,tp;
		for(int &i=cur[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			const lint v=eg[i].wi;
			if(v&&dep[y]==dep[x]+1&&(tp=dfs(y,std::min((lint)v,tt)))){
				eg[i].wi-=tp;
				eg[i^1].wi+=tp;
				if((tt-=tp)==0) break;
			}
		}
		return t-tt;
	}

	lint dinic(){
		lint ans=0;
		while(bfs()) ans+=dfs(0,1e10);
		return ans;
	}
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		for(int j=nxi(); j; --j) G0::add(i,n+nxi());
	}
	G0::get_lnk();
	for(int i=1; i<=n; ++i){
		for(int j=G0::fir[i]; j; j=G0::eg[j].nx){
			int k=G0::lnk[G0::eg[j].to];
			if(i!=k) G1::add(i,k,1e10);
		}
	}
	lint ans=0;
	for(int i=1; i<=n; ++i){
		int v=-nxi();
		if(v<0) G1::add(i,n+1,-v);
		if(v>0){
			ans+=v;
			G1::add(0,i,v);
		}
	}
	printf("%lld\n",-(ans-G1::dinic()));
	return 0;
}
