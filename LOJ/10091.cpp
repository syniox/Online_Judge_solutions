#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;
using lint=long long;

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<=y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>=y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
	static struct{
		template <class T> operator T(){
			T x=0;
			char c;
			while(((c=getchar())>'9'||c<'0')&&c!='-');
			const bool f=c=='-'&&(c=getchar());
			while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
			return f?-x:x;
		}
	}ni;
}
using namespace utils;
const int N=1e4+5;
const int M=5e4+5;
int n,m;

namespace G{
	int cnb,cnd,cnt,fir[N],dfn[N],low[N],bel[N],sz[N];
	vector<int> cnbe[N];
	bool vis[N];
	struct edge{
		int to,nx;
	}eg[M];

	inline void add(const int a,const int b){
		eg[++cnt]={b,fir[a]};
		fir[a]=cnt;
	}

	void tarjan(const int x){
		static int top,stk[N];
		dfn[x]=low[x]=++cnd;
		stk[++top]=x;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!dfn[y]) tarjan(y);
			if(!bel[y]) apn(low[x],low[y]);
		}
		if(dfn[x]!=low[x]) return;
		for(++cnb; ; ){
			++sz[cnb];
			bel[stk[top]]=cnb;
			if(stk[top--]==x) break;
		}
	}

	void dfsb(const int x){
		vis[x]=1;
		for(int y:cnbe[x]){
			if(!vis[y]) dfsb(y);
		}
	}

	void bind(){
		for(int x=1; x<=n; ++x){
			for(int i=fir[x]; i; i=eg[i].nx){
				int a=bel[x],b=bel[eg[i].to];
				cnbe[b].push_back(a);
			}
		}
		dfsb(1);
		for(int i=1; i<=cnb; ++i){
			if(!vis[i]){
				printf("%d\n",0);
				return;
			}
		}
		printf("%d\n",sz[1]);
	}
}

int main(){
	n=ni,m=ni;
	for(int i=1; i<=m; ++i){
		int a=ni,b=ni;
		G::add(a,b);
	}
	for(int i=1; i<=n; ++i){
		if(!G::bel[i]) G::tarjan(i);
	}
	G::bind();
	return 0;
}
