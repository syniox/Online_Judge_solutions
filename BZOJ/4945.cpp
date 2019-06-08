#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=5e4+5;
int n,m,spc[9],cspc,sidx[N];
char str[N];
struct _lim{
	int x,v1,y,v2;
}req[N<<1];

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
	int cnt,cnd,cscc,fir[N<<1],dfn[N<<1],bel[N<<1];
	bool col[N<<1];
	struct edge{
		int to,nx;
	}eg[N<<2];

	inline void add(const int a,const int b){
		//printf("add: %d->%d\n",a,b);
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	inline void clear(){
		cnt=cnd=cscc=0;
		memset(fir+1,0,(n<<1)*sizeof(fir[0]));
		memset(dfn+1,0,(n<<1)*sizeof(dfn[0]));
		memset(bel+1,0,(n<<1)*sizeof(bel[0]));
	}

	void tarjan(const int x){
		static int top,stk[N<<1],low[N<<1];
		stk[++top]=x;
		low[x]=dfn[x]=++cnd;
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

	void paint(){
		for(int i=1; i<=n; ++i){
			int b1=bel[i],b2=bel[i+n];
			if(b1>b2) std::swap(b1,b2);
			col[b1]=1,col[b2]=0;
		}
	}
}

int idx_p(const int x,const int v){
	return v-((str[x]-'a'+1)<v);
}

int real_p(const int x,const int v){
	return v+((str[x]-'a')<v);
}

bool jdg(){
	G::clear();
	for(int i=1; i<=m; ++i){
		int x=req[i].x,v1=req[i].v1,y=req[i].y,v2=req[i].v2;
		if(v1==str[x]-'a'+1) continue;
		int p1=idx_p(x,v1)-1,p2=idx_p(y,v2)-1;
		if(v2==str[y]-'a'+1){
			G::add(x+p1*n,x+(p1^1)*n);
		}
		else{
			G::add(x+p1*n,y+p2*n);
			G::add(y+(p2^1)*n,x+(p1^1)*n);
		}
	}
	for(int i=1; i<=n<<1; ++i){
		if(!G::bel[i]) G::tarjan(i);
	}
	for(int i=1; i<=n; ++i){
		if(G::bel[i]==G::bel[i+n]) return 0;
	}
	G::paint();
	for(int i=1; i<=n; ++i){
		putchar(real_p(i,(G::col[G::bel[i]]^1)+1)-1+'A');
	}
	puts("");
	return 1;
}

bool dfs(const int t){
	//枚举('a','c'),('b','c')即可覆盖能选3个点的所有情况
	if(t==cspc) return jdg();
	str[spc[t+1]]='a';
	if(dfs(t+1)) return 1;
	str[spc[t+1]]='b';
	return dfs(t+1);
}

int main(){
	n=nxi(),nxi();
	scanf("%s",str+1);
	for(int i=1; i<=n; ++i){
		if(str[i]=='x'){
			spc[++cspc]=i;
			sidx[i]=cspc;
		}
	}
	m=nxi();
	for(int i=1; i<=m; ++i){
		char c;
		req[i].x=nxi();
		while((c=getchar())>'Z'||c<'A');
		req[i].v1=c-'A'+1;
		req[i].y=nxi();
		while((c=getchar())>'Z'||c<'A');
		req[i].v2=c-'A'+1;
	}
	if(!dfs(0)) puts("-1");
	return 0;
}
