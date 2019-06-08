#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=105;
int n,m,tot,bel[N],val[N][N];

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

template <class T,size_t S>
class _disc{
	public:
		T v[N],*tl;
		int tot;
		_disc(){tl=v;}
		inline void ins(const T &x){
			*++tl=x;
		}
		inline void build(){
			std::sort(v+1,tl+1);
			tl=std::unique(v+1,tl+1)-1;
			tot=tl-v;
		}
		inline int ask(const T &x){
			return std::lower_bound(v+1,tl+1,x)-v;
		}
};
_disc <int,N> D;

namespace G{
	const int S=N*(N+1);
	int cnt=1,fir[S],cur[S],dep[S];
	struct edge{
		int to,wi,nx;
	}eg[S*3];

	inline void add(const int a,const int b,const int v){
		//printf("add: %d->%d,v%d\n",a,b,v);
		eg[++cnt]=(edge){b,v,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,0,fir[b]};
		fir[b]=cnt;
	}

	bool bfs(){
		static int que[S];
		memset(dep,0,(tot+2)*sizeof(dep[0]));
		int hd=0,tl=1;
		dep[0]=1;
		que[0]=0;
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
		return dep[tot+1];
	}

	lint dfs(const int x,const lint t){
		if(x==tot+1) return t;
		lint tt=t,tp;
		for(int &i=cur[x]; i; i=eg[i].nx){
			const int y=eg[i].to,v=eg[i].wi;
			if(v&&dep[y]==dep[x]+1&&(tp=(dfs(y,std::min((lint)v,tt))))){
				eg[i].wi-=tp;
				eg[i^1].wi+=tp;
				if((tt-=tp)==0) break;
			}
		}
		return t-tt;
	}

	lint dinic(){
		lint ans=0;
		while(bfs()){
			ans+=dfs(0,1e12);
		}
		return ans;
	}
}

inline int id_seg(const int l,const int r){
	return D.tot+((n-l)*(n-l+1)>>1)+(r-l+1);
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		bel[i]=nxi();
		D.ins(bel[i]);
	}
	D.build();
	tot=id_seg(1,n);
	lint ans=0;
	for(int i=1; i<=n; ++i){
		for(int j=i; j<=n; ++j){
			val[i][j]=nxi();
			if(i!=j&&val[i][j]>0) ans+=val[i][j];
		}
		val[i][i]-=bel[i];
		if(val[i][i]>0) ans+=val[i][i];
	}
	for(int i=1; i<=D.tot; ++i){
		G::add(i,tot+1,D.v[i]*D.v[i]*m);
	}
	for(int i=1; i<=n; ++i){
		int id=id_seg(i,i);
		G::add(id,D.ask(bel[i]),1e9);
		if(val[i][i]>0){
			G::add(0,id,val[i][i]);
		}
		if(val[i][i]<0){
			G::add(id,tot+1,-val[i][i]);
		}
	}
	for(int i=1; i<=n; ++i){
		for(int j=i+1; j<=n; ++j){
			const int id=id_seg(i,j);
			G::add(id,id_seg(i,j-1),1e9);
			G::add(id,id_seg(i+1,j),1e9);
			if(val[i][j]>0){
				G::add(0,id,val[i][j]);
			}
			if(val[i][j]<0){
				G::add(id,tot+1,-val[i][j]);
			}
		}
	}
	ans-=G::dinic();
	printf("%lld\n",ans);
	return 0;
}
