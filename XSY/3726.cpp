#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;
const int N=1.5e7+5;
const int mod=1e9+7;
int fac[N],ifac[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
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

inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline int C(const int x,const int y){
	if(y<0) return 0;
	return (lint)fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}

int main(){
	int n=nxi(),q=nxi();
	fac[0]=1;
	for(int i=1; i<=n*3; ++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	ifac[n*3]=fpow(fac[n*3],mod-2);
	for(int i=n*3; i>=1; --i){
		ifac[i-1]=(lint)ifac[i]*i%mod;
	}
	int ans=0;
	for(int i=0; i<=n-q; ++i){
		ans=(ans+(lint)(i+q)*(C(i*2+q-1,i)-C(i*2+q-1,i-1)+mod))%mod;
	}
	ans=(lint)ans*ifac[q]%mod*fac[q-1]%mod;
	ans=(lint)ans*(C(q*2-4,q-2)-C(q*2-4,q-3)+mod)%mod;
	printf("%d\n",ans);
}
