#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
const int mod=998244353;
int n,q,fac[205],dp[205];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
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
//第i行选j: j向i卖弱
//f[i][j]: 第q行开始往上i行 j个不满足条件的方案数

inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	fac[0]=1;
	for(int i=1; i<=205; ++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	for(int T=nxi(); T; --T){
		n=nxi(),q=nxi();
		memset(dp,0,sizeof(dp));
		for(int i=0; i<=q; ++i){
			for(int j=i; j; --j){//应否直接在此带负号？
				dp[j]=(dp[j]-(lint)dp[j-1]*(i-j+1))%mod;
			}
			dp[0]=1;
		}
		int ans=0;
		for(int i=0; i<=q; ++i){
			ans=(ans+(lint)dp[i]*fac[q-i]%mod*fpow(q-i,n-q))%mod;
		}
		printf("%d\n",(ans+mod)%mod);
	}
	return 0;
}
