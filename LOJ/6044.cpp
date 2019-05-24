#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=5e5+5;
int fac[N],ifac[N];

namespace utils{
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

const int n=nxi(),q=nxi(),mod=nxi();

template <class T> inline int fpow(int x,T t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

void init(){
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
	init();
	int a=q,b=n-q;
	int res=(lint)fpow(a,b-1)*fpow(b,a-1)%mod;
	printf("%lld\n",(lint)C(n-1,a-1)*res%mod);
}
