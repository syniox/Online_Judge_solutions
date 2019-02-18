#include <iostream>
#include <cstdio>
#include <cstring>
const int N=65;
int n,m;

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int get_pep(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return (x<<1)+(c=='h');
}

namespace G{
	int cnt,cnd,cnf,fir[N],bel[N],dfn[N],low[N];
	struct edge{
		int to,nx;
	}eg[N*N];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	inline void init(){
		cnt=cnd=cnf=0;
		memset(dfn,0,sizeof(dfn));
		memset(bel,0,sizeof(bel));
		memset(fir,0,sizeof(fir));
	}

	inline void tarjan(const int x){
		static int top,stk[N];
		stk[++top]=x;
		low[x]=dfn[x]=++cnd;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!dfn[y]){
				tarjan(y);
				apn(low[x],low[y]);
			}
			else if(!bel[y]){
				apn(low[x],dfn[y]);
			}
		}
		if(dfn[x]!=low[x]) return;
		++cnf;
		for(int i=stk[top--]; ; i=stk[top--]){
			bel[i]=cnf;
			if(i==x) break;
		}
	}

	inline bool jdg(){
		for(int i=0; i<n<<1; i+=2){
			if(bel[i]==bel[i^1]) return 0;
		}
		return 1;
	}
}

int main(){
	while(n=nxi(),m=nxi(),n||m){
		G::init();
		for(int i=1; i<=m; ++i){
			const int x=get_pep(),y=get_pep();
			G::add(x,y^1);
			G::add(y,x^1);
		}
		G::add(0,1);
		for(int i=0; i<n<<1; ++i){
			if(!G::bel[i]) G::tarjan(i);
		}
		if(!G::jdg()) puts("bad luck");
		else{
			for(int i=1; i<n; ++i){
				using G::bel;
				if(bel[i<<1]<bel[i<<1|1]) printf("%dh ",i);
				else printf("%dw ",i);
			}
			puts("");
		}
	}
	return 0;
}
