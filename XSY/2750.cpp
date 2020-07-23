#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long lint;
const int N=254,V=250*250*2+5;
int n,m,q,val[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
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


inline int getid(const int bel,const int x,const bool f){
	return ((bel-1)*n+x)*2+f;
}

namespace G{//编号2~n*m*2+1
	int cnt,cnd,cnf,fir[V],dfn[V],low[V],bel[V];//先出栈的为拓扑序后的
	struct edge{
		int to,nx;
	}eg[V*2+N*N*2+N*N*N*2];

	inline void lnk(int a,int b){
		//eprintf("lnk: %d->%d\n",a,b);
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
		a^=1,b^=1;
		//eprintf("lnk: %d->%d\n",b,a);
		eg[++cnt]=(edge){a,fir[b]};
		fir[b]=cnt;
	}

	void tarjan(const int x){
		static int stk[V],top;
		stk[++top]=x;
		low[x]=dfn[x]=++cnd;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!dfn[y]) tarjan(y);
			if(!bel[y]) apn(low[x],low[y]);
		}
		if(low[x]!=dfn[x]) return;
		++cnf;
		for(;;){
			bel[stk[top]]=cnf;
			if(stk[top--]==x) break;
		}
	}
}

namespace T{
	int cnt,fir[N],fa[N],dep[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs_eg(const int x){
		static int buk[N];
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa[x]) continue;
			for(int j=1; j<=m; ++j){
				G::lnk(getid(y,j,1),getid(x,j,1));
			}
			fa[y]=x;
			dep[y]=dep[x]+1;
			dfs_eg(y);
		}
		int cnt=0;
		for(int i=fir[x]; i; i=eg[i].nx){
			if(eg[i].to!=fa[x]) buk[++cnt]=eg[i].to;
		}
		for(int i=1; i<=cnt; ++i){
			for(int j=i+1; j<=cnt; ++j){
				for(int k=1; k<=m; ++k){
					G::lnk(getid(buk[i],k,1),getid(buk[j],k,0));
				}
			}
		}
	}

	void setlim(const int a,const int b,const int c){
		for(int i=fir[c]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa[c]) continue;
			G::lnk(getid(y,a,1),getid(y,b,0));
		}
		G::lnk(getid(c,a,0),getid(c,b,1));
	}
}

inline bool intr(const int x,const int r){
	return G::bel[getid(r,x,1)]<G::bel[getid(r,x,0)];
}

int main(){
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		T::add(a,b),T::add(b,a);
	}
	T::dfs_eg(1);
	for(int i=1; i<=q; ++i){
		const int a=nxi(),b=nxi(),c=nxi();
		T::setlim(a,b,c);
	}
	for(int i=1; i<=m; ++i){
		G::lnk(getid(1,i,0),getid(1,i,1));
	}
	for(int i=2; i<=n*m*2+1; ++i){
		if(!G::bel[i]) G::tarjan(i);
	}
	for(int i=1; i<=m; ++i){
		int pos=0;
		for(int j=1; j<=n; ++j){
			using G::bel;
			assert(bel[getid(j,i,1)]!=bel[getid(j,i,0)]);
			if(intr(i,j)&&T::dep[j]>=T::dep[pos]){
				pos=j;
			}
		}
		printf("%d ",pos);
	}
	puts("");
	return 0;
}
