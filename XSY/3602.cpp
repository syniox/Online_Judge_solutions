#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=1e5+5;
int n,qn[N],qx[N],qt[N];

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

namespace G{
	int cnt,fir[N],an[N],ax[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs(const int x,const int f){
		an[x]=0,ax[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==f) continue;
			dfs(y,x);
			if(an[y]>ax[y]){
				an[x]=1,ax[x]=0;
				return;
			}
			an[x]+=an[y];
			ax[x]+=ax[y];
		}
		apn(ax[x],qx[x]);
		apx(an[x],qn[x]);
	}
}

bool solve(const int tgt){
	for(int i=1; i<=n; ++i){
		if((qx[i]=tgt-qt[i])<qn[i]) return 0;
	}
	G::dfs(1,1);
	return G::an[1]<=tgt&&G::ax[1]>=tgt;
}

int main(){
	n=nxi();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	for(int i=nxi(); i; --i){
		const int x=nxi();
		apx(qn[x],nxi());
	}
	for(int i=nxi(); i; --i){
		const int x=nxi();
		apx(qt[x],nxi());
	}
	int l=0,r=n+1,mid;
	while(l!=r){
		mid=(l+r)>>1;
		if(solve(mid)) r=mid;
		else l=mid+1;
	}
	printf("%d\n",l<=n?l:-1);
	return 0;
}
