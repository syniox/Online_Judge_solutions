#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=55;
int n,m,all,minf,tot[N],sumt[N];
bool nd[N*2];
struct edge{
	int f,x,y;
}eg[355];

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

bool getcol(const int x){
	assert(x!=minf);
	return (x<minf?x+n-minf:x-minf)&1;
}

namespace G{
	int cnt=1,fir[N*2],dep[N*2];
	struct edge{
		int to,wi,nx;
	}eg[905];

	inline void clear(){
		cnt=1;
		memset(fir,0,sizeof(fir));
	}

	inline void add(const int a,const int b,const int v){
		//fprintf(stderr,"add: %d->%d v%d\n",a,b,v);
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,0,fir[b]};
		fir[b]=cnt;
	}

	bool bfs(){
		static int que[N*2];
		memset(dep,-1,sizeof(dep));
		dep[0]=0;
		int hd=0,tl=1;
		while(hd!=tl){
			const int x=que[hd++];
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(eg[i].wi&&dep[y]==-1){
					que[tl++]=y;
					dep[y]=dep[x]+1;
				}
			}
		}
		return dep[all+1]!=-1;
	}

	int dfs(const int x,const int t){
		if(x==all+1) return t;
		int tt=t,tp;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to,v=eg[i].wi;
			if(v&&dep[y]==dep[x]+1&&(tp=dfs(y,std::min(tt,v)))){
				eg[i].wi-=tp;
				eg[i^1].wi+=tp;
				if(!(tt-=tp)) return t;
			}
		}
		return t-tt;
	}

	int solve(const bool *ban){
		int bcnt=0;
		clear();
		for(int i=1; i<=n; ++i){
			for(int j=sumt[i-1]+1; j<=sumt[i]; ++j){
				if(ban[j]){
					++bcnt;
					continue;
				}
				if(getcol(i)) add(0,j,1);
				else add(j,all+1,1);
			}
		}
		for(int i=1; i<=m; ++i){
			int gx=sumt[::eg[i].f-1]+::eg[i].x;
			int gy=sumt[::eg[i].f==n?0:(::eg[i].f)]+::eg[i].y;
			if(ban[gx]||ban[gy]) continue;
			if(!getcol(::eg[i].f)) std::swap(gx,gy);
			add(gx,gy,1);
		}
		int ans=0;
		while(bfs()){
			ans+=dfs(0,1e8);
		}
		return all-bcnt-ans;
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=m; ++i){
		eg[i].x=nxi(),eg[i].y=nxi(),eg[i].f=nxi();
		apx(tot[eg[i].f],eg[i].x);
		apx(tot[eg[i].f%n+1],eg[i].y);
	}
	for(int i=1; i<=n; ++i){
		sumt[i]=sumt[i-1]+tot[i];
		if(!minf||tot[i]<tot[minf]) minf=i;
	}
	assert(minf);
	all=sumt[n];
	int ans=0;
	for(int i=0; i<1<<tot[minf]; ++i){
		static bool nd[N*2],ban[N*2];
		memset(ban,0,sizeof(ban));
		memset(nd,0,sizeof(nd));
		int cnt=0;
		for(int j=1; j<=tot[minf]; ++j){
			ban[sumt[minf-1]+j]=1;
			cnt+=nd[sumt[minf-1]+j]=i>>(j-1)&1; 
		}
		for(int j=1; j<=m; ++j){
			int gx=sumt[eg[j].f-1]+eg[j].x;
			int gy=sumt[eg[j].f==n?0:eg[j].f]+eg[j].y;
			if(nd[gx]) ban[gy]=1;
			if(nd[gy]) ban[gx]=1;
		}
		apx(ans,cnt+G::solve(ban));
	}
	printf("%d\n",ans);
	return 0;
}
