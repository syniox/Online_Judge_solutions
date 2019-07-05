#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <bitset>
typedef long long lint;
const int N=5005;
int n,q,val[N];
bool dp[N],invld[N];
std::bitset <N> pre[N],suf[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
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

bool jdg(const int x){
	static int sum[N];
	sum[0]=1;
	for(int i=1; i<=q; ++i){
		sum[i]=sum[i-1]+suf[x+1][i];
	}
	int lim=std::max(1,q-val[x]);
	for(int i=1; i<q; ++i){
		if(pre[x-1][i]&&sum[q-i-1]-(i>lim?0:sum[lim-i])) return 1;
	}
	return sum[q]-sum[lim];
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=std::min(q+1,nxi());
	}
	pre[0][0]=1;
	for(int i=1; i<=n; ++i){
		pre[i]=pre[i-1]|pre[i-1]<<val[i];
	}
	suf[n+1][0]=1;
	for(int i=n; i>=1; --i){
		suf[i]=suf[i+1]|suf[i+1]<<val[i];
	}
	int ans=0;
	for(int i=1; i<=n; ++i){
		ans+=!jdg(i);
	}
	printf("%d\n",ans);
	return 0;
}
