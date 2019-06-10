#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e6+5;
const int mod=998244353;
int n,q,fac[N],ifac[N];

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

template <class T>
inline int fpow(int x,T t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

void init_fac(){
	fac[0]=1;
	for(int i=1; i<N; ++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	ifac[N-1]=fpow(fac[N-1],mod-2)%mod;
	for(int i=N-1; i; --i){
		ifac[i-1]=(lint)ifac[i]*i%mod;
	}
}

inline int C(const int x,const int y){
	assert(x>=0&&y>=0);
	if(x<y) return 0;
	return (lint)fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}

int solve(const int s0,const int s1){
	assert(s0+s1==n);
	if(s0<2) return assert(s1),0;
	int ans=0;
	{//0|0
		ans=(ans+2ll*C(n-2,s0-2))%mod;
		if(s0>2) ans=(ans-C(n-3,s0-3)+mod)%mod;
	}
	{//00 | 00
		const int lim=std::min(s1*2-1,(s0-4)*2+1);
		assert(lim<=n-4);
		for(int i=1; i<=lim; i+=2){
			const int lim_dn=std::max(0,i-((n>>1)-1));
			const int lim_up=std::min(i-1,(n>>1)-2);
			ans=(ans+(lint)(lim_up-lim_dn+1)*C(n-4-i,s0-4-(i>>1)))%mod;
		}
	}
	{//11 | 00
		const int lim=std::min(s0-2,s1-2)*2;
		assert(lim<=n-4);
		for(int i=2; i<=lim; i+=2){
			const int wgt=std::min(i,2*(((n>>1)-2)-((i>>1)-1)));
			if(wgt<0) break;
			ans=(ans+(lint)wgt*C(n-4-i,s0-2-(i>>1)))%mod;
		}
	}
	{// | 00
		for(int i=1; i<=(n>>1)-1; ++i){
			if((s1-(((n>>1)+i+1)>>1))<0) break;
			ans=(ans+2ll*C((n>>1)-i-1,s1-(((n>>1)+i+1)>>1)))%mod;
		}
	}
	ans+=(s0==s1+1);
	ans=(lint)ans*fac[s0]%mod*fac[s1]%mod;
	return ans;
}

int main(){
	n=nxi(),q=nxi();
	init_fac();
	if(n==1||q==1||q==n){
		puts(n==1?"1":"0");
		return 0;
	}
	printf("%d\n",(solve(q,n-q)-solve(q-1,n-q+1)+mod)%mod);
	return 0;
}
