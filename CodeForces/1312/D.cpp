#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=2e5+5;
const int mod=998244353;
int fac[N],ifac[N];

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

template <class T> inline int fpow(int x,T t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline void init(const int n){
	fac[0]=1;
	for(int i=1; i<=n; ++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	ifac[n]=fpow(fac[n],mod-2);
	for(int i=n; i>=1; --i){
		ifac[i-1]=(lint)ifac[i]*i%mod;
	}
}

inline int C(const int x,const int y){
	if(x<y) return 0;
	return (lint)fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}

int main(){
	const int n=nxi(),m=nxi();
	if(n==2){
		puts("0");
		return 0;
	}
	init(m);
	int ans=0;
	for(int i=n-1; i<=m; ++i){
		ans=(ans+(lint)C(i-1,n-2)*(n-2)%mod*fpow(2,n-3))%mod;
	}
	printf("%d\n",ans);
	return 0;
}
