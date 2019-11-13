#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1005;
int n,q,va[N],vb[N],vc[N];

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

int main(){
	static lint dp[N*10];
	for(int T=nxi(); T; --T){
		n=nxi(),q=nxi();
		memset(dp,10,(q+1)*sizeof(dp[0]));
		dp[0]=0;
		for(int i=1; i<=n; ++i){
			va[i]=nxi();
		}
		for(int i=1; i<=n; ++i){
			vb[i]=nxi();
		}
		for(int i=1; i<=n; ++i){
			vc[i]=nxi();
		}
		int sb=0;
		for(int i=1; i<=n; ++i){
			static int que[N*10];
			int hd=0,tl=0;
			sb=std::min(q,sb+vb[i]);
			for(int j=sb-va[i]; j>=0&&j>sb-vb[i]; --j){
				for(; tl!=hd&&dp[j]<dp[que[tl-1]]; --tl);
				que[tl++]=j;
			}
			for(int j=sb; j>=va[i]; --j){
				for(; hd<tl&&j-que[hd]<va[i]; ++hd);
				if(j>=vb[i]){
					for(; tl!=hd&&dp[j-vb[i]]<=dp[que[tl-1]]; --tl);
					que[tl++]=j-vb[i];
				}
				if(hd!=tl) apn(dp[j],dp[que[hd]]+vc[i]);
			}
		}
		if(dp[q]>=1e16) puts("IMPOSSIBLE!!!");
		else printf("%lld\n",dp[q]);
	}
	return 0;
}
