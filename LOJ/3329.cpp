#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
#include <set>
typedef long long lint;
using namespace std;
const int N=2e5+5;
set<int> pst;
int n,q;

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
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

namespace G{
	int cnt,fir[N],dgr[N],fa[N];
	int dep[N],son[N],sz[N],top[N],dfn[N];
	struct edge{
		int to,nx;
	}eg[N<<1];
	inline bool cmp_dfn(const int a,const int b){
		return dfn[a]<dfn[b];
	}

	inline void add(const int a,const int b){
		++dgr[a];
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}
	bool is_chain(){
		bool f=1;
		f&=dgr[1]==1;
		for(int i=2; f&&i<=n; ++i){
			f&=dgr[i]<=2;
		}
		return f;
	}

	void dfs_son(const int x){
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(sz[y]) continue;
			dep[y]=dep[x]+1;
			fa[y]=x;
			dfs_son(y);
			if(sz[y]>sz[son[x]]) son[x]=y;
			sz[x]+=sz[y];
		}
	}
	void dfs_top(const int x){
		static int cnd;
		top[x]=son[fa[x]]==x?top[fa[x]]:x;
		dfn[x]=++cnd;
		for(int i=fir[x]; i; i=eg[i].nx){
			if(!dfn[eg[i].to]) dfs_top(eg[i].to);
		}
	}

	inline int qlca(int x,int y){
		while(top[x]!=top[y]){
			if(dep[top[x]]>dep[top[y]]) x=fa[top[x]];
			else y=fa[top[y]];
		}
		return dep[x]<dep[y]?x:y;
	}

	int solve(){
		if(pst.empty()) return 0;
		static int buk[N],stk[N],res[N];
		int cnt=0,top=0,cres=0;
		for(set<int>::iterator it=pst.begin(); it!=pst.end(); ++it){
			buk[++cnt]=*it;
		}
		sort(buk+1,buk+cnt+1,cmp_dfn);
		stk[++top]=buk[1];
		sz[buk[1]]=0;
		for(int i=2; i<=cnt; ++i){
			int lca=qlca(stk[top],buk[i]);
			if(dep[lca]<dep[stk[top]]){
				for(; top>1&&dep[stk[top-1]]>dep[lca]; --top){
					sz[stk[top-1]]+=++sz[stk[top]];
					res[++cres]=sz[stk[top]];
				}
				res[++cres]=++sz[stk[top--]];
				if(stk[top]!=lca){
					sz[lca]=sz[stk[top+1]];
					stk[++top]=lca;
				}
				else{
					sz[lca]+=++sz[stk[top+1]];
				}
			}
			assert(buk[i]!=lca);
			sz[buk[i]]=0;
			stk[++top]=buk[i];
		}
		for(; top; --top){
			sz[stk[top-1]]+=++sz[stk[top]];
			res[++cres]=sz[stk[top]];
		}
		sort(res+1,res+cres+1);
		res[cres+1]=1e9;
		int l=0,r=cres,mid;//最后一个res[i]<=cres-i的位置
		while(l!=r){
			mid=(l+r+1)>>1;
			if(res[mid]<=cres-mid) l=mid;
			else r=mid-1;
		}
		return min(max(res[l],cres-l),max(res[l+1],cres-l-1));
	}
}

void solveA(){
	for(int q=ni; q--; ){
		if((int)ni==1){
			pst.insert((int)ni);
		}else{
			pst.erase((int)ni);
		}
		printf("%d\n",G::solve());
	}
}

void solveB(){
	int cnt=0;
	for(int q=ni; q--; ){
		if((int)ni==1){
			(int)ni,++cnt;
		}else{
			(int)ni,--cnt;
		}
		printf("%d\n",(cnt+1)>>1);
	}
}

int main(){
	n=ni;
	for(int i=1; i<n; ++i){
		const int x=ni,y=ni;
		G::add(x,y),G::add(y,x);
	}
	G::dfs_son(1);
	G::dfs_top(1);
	if(n<=1e5) solveA();
	else if(G::is_chain()) solveB();
	return 0;
}
