#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
int n,m;
//[1,n]晋级 [n+1,2n]不晋级

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
	int cnt,cscc,fir[N<<1],dfn[N<<1],bel[N<<1];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void clear(){
		cnt=cscc=0;
		memset(fir+1,0,(n<<1)*sizeof(fir[0]));
		memset(dfn+1,0,(n<<1)*sizeof(dfn[0]));
		memset(bel+1,0,(n<<1)*sizeof(bel[0]));
	}

	inline void add(const int a,const int b){
		//printf("add: %d->%d\n",a,b);
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void tarjan(const int x){
		static int top,stk[N<<1],low[N<<1];
		stk[++top]=x;
		low[x]=dfn[x]=++top;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!dfn[y]) tarjan(y);
			if(!bel[y]) apn(low[x],low[y]);
		}
		if(dfn[x]!=low[x]) return;
		++cscc;
		for(int i=stk[top--]; ; i=stk[top--]){
			bel[i]=cscc;
			if(i==x) break;
		}
	}

	bool jdg_scc(){
		for(int i=1; i<=n; ++i){
			if(!bel[i]) tarjan(i);
		}
		for(int i=1; i<=n; ++i){
			if(bel[i]==bel[i+n]) return 0;
		}
		return 1;
	}

	bool bfs(){
		static bool vis[N<<1];
		static int que[N<<1];
		memset(vis+1,0,(n<<1)*sizeof(vis[0]));
		int hd=0,tl=1;
		que[0]=1;
		vis[1]=1;
		while(hd!=tl){
			const int x=que[hd++];
			for(int i=fir[x]; i; i=eg[i].nx){
				const int y=eg[i].to;
				if(!vis[y]){
					que[tl++]=y;
					vis[y]=1;
				}
			}
		}
		for(int i=1; i<=n; ++i){
			if(vis[i]&&vis[i+n]) return 0;
		}
		return 1;
	}
}

inline int rev_st(const int x){
	return x<=n?x+n:x-n;
}

int main(){
	while(~scanf("%d%d",&n,&m)){
		G::clear();
		for(int i=1; i<=m; ++i){
			int a=nxi(),b=nxi();
			if(a<0) a=-a+n;
			if(b<0) b=-b+n;
			G::add(rev_st(a),b);
			G::add(rev_st(b),a);
		}
		if(!G::jdg_scc()){
			puts("no");
			continue;
		}
		puts(G::bfs()?"yes":"no");
	}
	return 0;
}
