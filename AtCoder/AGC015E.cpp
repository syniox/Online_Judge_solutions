#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=2e5+5;
const int mod=1e9+7;
int n,dp[N];//前缀和
struct _pair{
	int x,y;
}dt[N],spc[N];
//dt: pos,v
//spc: l,r

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline bool _pr_cmp_y(const _pair &a,const _pair &b){
	return a.y<b.y;
}

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

namespace B{
	int tr[N];
	inline void clear(){
		memset(tr+1,0,n*sizeof(int));
	}
	inline void apl(int x,const int v){
		for(; tr[x]<v&&x<=n; x+=x&-x) tr[x]=v;
	}
	inline int ask(int x){
		int ans=0;
		for(; x; x-=x&-x) apx(ans,tr[x]);
		return ans;
	}
}

template <class T> class _Disc{
	public:
		T buk[N],*pt;
		int tot;

		_Disc(){pt=buk;}
		inline void insert(const T &v){
			*pt++=v;
		}
		inline void build(){
			std::sort(buk,pt);
			pt=std::unique(buk,pt);
			tot=pt-buk;
		}
		inline int ask(const T &v){
			return std::lower_bound(buk,pt,v)-buk+1;
		}
};
_Disc <int> D;

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	n=nxi();
	for(int i=1; i<=n; ++i){
		dt[i].x=nxi(),dt[i].y=nxi();
		D.insert(dt[i].x);
	}
	D.build();
	for(int i=1; i<=n; ++i){
		dt[i].x=D.ask(dt[i].x);
	}
	std::sort(dt+1,dt+n+1,_pr_cmp_y);
	for(int i=1; i<=n; ++i){
		int res=B::ask(n-dt[i].x+1);
		spc[i].x=res?n-res+1:i;
		B::apl(n-dt[i].x+1,n-i+1);
	}
	B::clear();
	for(int i=n; i>=1; --i){
		int res=B::ask(dt[i].x);
		spc[i].y=res?res:i;
		B::apl(dt[i].x,i);
	}
	std::sort(spc+1,spc+n+1,_pr_cmp_y);
	dp[0]=1;
	for(int i=1,j=1; i<=n; ++i){
		dp[i]=dp[i-1];
		for(; j&&spc[j].y==i; ++j){
			dp[i]=(dp[i]+(lint)(dp[i]-(spc[j].x>1?dp[spc[j].x-2]:0)+mod))%mod;
		}
	}
	printf("%d\n",(dp[n]-dp[n-1]+mod)%mod);
	return 0;
}
