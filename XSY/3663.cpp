#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e6+5;
int n,ans;

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

namespace G{
	int cnt,fir[N],fa[N],sz[N],buk_sz[N],fa_sz[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	inline int nf_sz(const int x){
		assert(x>0);
		return buk_sz[x]-fa_sz[x];
	}

	void dfs_sz(const int x){
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(sz[y]) continue;
			fa[y]=x;
			dfs_sz(y);
			sz[x]+=sz[y];
		}
		++buk_sz[sz[x]];
	}

	void dfs_ans(const int x){
		int tgt=(n-sz[x])>>1;
		if(sz[x]*2<n&&ans<sz[x]&&(fa_sz[sz[x]*2]||fa_sz[n-sz[x]])){
			ans=sz[x];
		}
		if(ans<tgt&&(n-sz[x])%2==0&&fa_sz[tgt+sz[x]]){
			ans=tgt;
		}
		++fa_sz[sz[x]];
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y!=fa[x]) dfs_ans(y);
		}
		if(nf_sz(sz[x])) apx(ans,sz[x]);
		if(!((n-sz[x])&1)&&tgt>=sz[x]&&nf_sz(tgt)) apx(ans,tgt);
		if(sz[x]*3<=n&&nf_sz(n-sz[x]*2)) apx(ans,sz[x]);
		--fa_sz[sz[x]];
	}
}

int main(){
	n=nxi();
	for(int i=1; i<n; ++i){
		int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	G::dfs_sz(1);
	G::dfs_ans(1);
	printf("%d\n",ans);
	return 0;
}
