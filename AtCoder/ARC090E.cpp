#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <queue>
typedef long long lint;
const int N=1e5+5;
const int mod=1e9+7;
int n,m,qs,qt,scnt[N],tcnt[N];
lint totl,sdis[N],tdis[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

namespace G{
	int cnt,fir[N];
	struct edge{
		int to,wi,nx;
	}eg[N<<2];
	struct data{
		int x;
		lint v;
		friend bool operator < (const data &a,const data &b){
			return a.v>b.v;
		}
	};

	inline void add(const int a,const int b,const int v){
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
	}

	void dij(const int st,lint *dis,int *dcnt){
		static bool vis[N];
		std::priority_queue <data> pq;
		memset(dis+1,10,n*sizeof(dis[0]));
		memset(vis+1,0,n*sizeof(vis[0]));
		dis[st]=0,dcnt[st]=1;
		pq.push((data){st,0});
		while(!pq.empty()){
			const int x=pq.top().x;
			pq.pop();
			if(vis[x]) continue;
			vis[x]=1;
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				const lint v=dis[x]+eg[i].wi;
				if(dis[y]>v){
					dcnt[y]=0;
					dis[y]=v;
					pq.push((data){y,v});
				}
				if(dis[y]==v){
					dcnt[y]=(dcnt[y]+dcnt[x])%mod;
				}
			}
		}
	}

	int calc(const int x){
		int res=0;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			const lint dx=sdis[x],dy=tdis[y];
			if(dx+eg[i].wi+dy==totl&&dx*2<totl&&dy*2<totl){
				int tmp=(lint)scnt[x]*tcnt[y]%mod;
				res=(res+(lint)tmp*tmp)%mod;
			}
		}
		return res;
	}
}

int main(){
	n=nxi(),m=nxi(),qs=nxi(),qt=nxi();
	for(int i=1; i<=m; ++i){
		const int a=nxi(),b=nxi(),v=nxi();
		G::add(a,b,v);
		G::add(b,a,v);
	}
	G::dij(qs,sdis,scnt);
	G::dij(qt,tdis,tcnt);
	assert(sdis[qt]==tdis[qs]);
	totl=sdis[qt];
	int ans=(lint)scnt[qt]*tcnt[qs]%mod;
	for(int i=1; i<=n; ++i){
		if(sdis[i]==tdis[i]&&sdis[i]+tdis[i]==totl){
			int tmp=(lint)scnt[i]*tcnt[i]%mod;
			ans=(ans-(lint)tmp*tmp)%mod;
		}
		ans=(ans-G::calc(i))%mod;
	}
	printf("%d\n",(ans+mod)%mod);
	return 0;
}
