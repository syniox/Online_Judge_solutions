#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long lint;
const int mod=1e4+7;
int n,q,fac[mod],ifac[mod];

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

inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline int C(const int x,const int y){
	assert(x<mod&&y<mod);
	if(x<y) return 0;
	return fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}

int ex_C(const int x,const int y){
	if(x<y||y<0) return 0;
	if(x<mod&&y<mod) return C(x,y);
	return ex_C(x/mod,y/mod)*C(x%mod,y%mod)%mod;
}

int main(){
	fac[0]=1;
	for(int i=1; i<mod; ++i){
		fac[i]=fac[i-1]*i%mod;
	}
	ifac[mod-1]=fpow(fac[mod-1],mod-2);
	for(int i=mod-1; i; --i){
		ifac[i-1]=ifac[i]*i%mod;
	}
	n=nxi()-1,q=nxi();
	int ans=ex_C(n*2,n);
	for(int i=0; ; ++i){
		if(n-(i+1)*q<0&&n-1-i*q<0&&n-(i+1)*q+1<0) break;
		int res=(ex_C(n*2,n-(i+1)*q)*2-ex_C(n*2,n-1-i*q)-ex_C(n*2,n-(i+1)*q+1))%mod;
		ans=(ans+res+mod)%mod;
	}
	printf("%d\n",ans);
	return 0;
}
