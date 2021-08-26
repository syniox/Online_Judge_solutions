#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
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

const int N=3e5+5;
int n;

struct base_tr{
	vector<int> eg[N];
	int fa[N];
	void adde(const int a,const int b){
		eg[a].push_back(b);
	}
	void input(){
		for(int i=2; i<=n; ++i) adde(fa[i]=ni,i);
	}
};

struct K_tr:base_tr{ // 2
	int cnd,tr[N],dfn[N],top[N],sz[N],son[N],idx[N];
	inline void reset(){
		cnd=0;
		for(int i=1; i<=n; ++i) eg[i].clear();
		memset(tr+1,0,n*sizeof(int));
		memset(son+1,0,n*sizeof(int));
	}
	void addv(int x,const int v){
		for(; x<=n; x+=x&-x) tr[x]+=v;
	}
	int qsum(int x){
		int ans=0;
		for(; x; x-=x&-x) ans+=tr[x];
		return ans;
	}
	int qsum(const int l,const int r){
		if(l>r) return 0;
		return qsum(r)-qsum(l-1);
	}
	void dfs1(const int x){
		sz[x]=1;
		for(int y:eg[x]){
			dfs1(y);
			if(sz[y]>sz[son[x]]) son[x]=y;
			sz[x]+=sz[y];
		}
	}
	void dfs2(const int x,const int t){
		top[x]=t;
		dfn[x]=++cnd;
		idx[cnd]=x;
		if(son[x]) dfs2(son[x],t);
		for(int y:eg[x]){
			if(y!=son[x]) dfs2(y,y);
		}
	}
	int q2root(int x){
		for(; x&&!qsum(dfn[top[x]],dfn[x]); x=fa[top[x]]);
		if(x==0) return 0;
		assert(qsum(dfn[top[x]],dfn[x])==1);
		int l=dfn[top[x]],r=dfn[x];
		while(l!=r){
			int mid=(l+r)>>1;
			if(!qsum(l,mid)) l=mid+1;
			else r=mid;
		}
		return idx[l];
	}
}K;

struct S_tr:base_tr{
	int ans,cnt;
	void reset(){
		ans=cnt=0;
		for(int i=1; i<=n; ++i) eg[i].clear();
	}
	void dfs(const int x){
		int reset=K.q2root(x);
		if(reset){
			K.addv(K.dfn[reset],-1);
			K.addv(K.dfn[x],1);
		}else if(!K.qsum(K.dfn[x]+1,K.dfn[x]+K.sz[x]-1)){
			reset=-1;
			K.addv(K.dfn[x],1);
			++cnt;
		}
		apx(ans,cnt);
		for(int y:eg[x]){
			dfs(y);
		}
		if(reset) --cnt,K.addv(K.dfn[x],-1);
		if(reset>0) ++cnt,K.addv(K.dfn[reset],1);
	}
}S;

int main(){
	for(int T=ni; T--; ){
		n=ni;
		S.reset(),K.reset();
		S.input(),K.input();
		K.dfs1(1);
		K.dfs2(1,1);
		S.dfs(1);
		printf("%d\n",S.ans);
	}
	return 0;
}
