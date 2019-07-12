#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
const int mod=1e9+7;
int fac[N];

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

int main(){
	const int n=nxi(),m=nxi();
	if(n>m+1||m>n+1){
		puts("0");
		return 0;
	}
	fac[0]=1;
	for(int i=1; i<=std::max(n,m); ++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	if(n==m){
		printf("%lld\n",2ll*fac[n]%mod*fac[n]%mod);
	}
	else{
		printf("%lld\n",(lint)fac[m]*fac[n]%mod);
	}
	return 0;
}
