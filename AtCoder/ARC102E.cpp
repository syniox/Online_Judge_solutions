#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
using lint=long long;
const int mod=998244353;
const int N=2005;
int fac[N<<1],ifac[N<<1];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<=y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>=y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
	static struct{
		template <class T> operator T(){
			T x=0;
			char c;
			while(((c=getchar())>'9'||c<'0')&&c!='-');
			const bool f=c=='-'&&(c=getchar());
			while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
			return f?-x:x;
		}
	}ni;
}
using namespace utils;

inline int fpow(int x,int t){
	int ans=1;
	for(; t; t>>=1,x=(lint)x*x%mod){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline void init(const int l){
	fac[0]=1;
	for(int i=1; i<=l; ++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	ifac[l]=fpow(fac[l],mod-2);
	for(int i=l; i>=1; --i){
		ifac[i-1]=(lint)ifac[i]*i%mod;
	}
}

inline int C(const int x,const int y){
	if(x<y||y<0) return 0;
	return (lint)fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}

int solve(const int ct,const int nct,const int n){
	int ans=0,tot=ct*2+nct;
	for(int i=1; i<=ct&&i*2<=n; ++i){
		int wgt=i&1?1:mod-1;
		ans=(ans+(lint)C(ct,i)*C(n-i*2+tot-1,tot-1)%mod*wgt)%mod;
	}
	return (C(n+tot-1,tot-1)-ans+mod)%mod;
}

int main(){
	int q=ni,n=ni;
	init(n+q);
	for(int i=2; i<=q*2; ++i){
		if(i&1){
			int ct=min(i>>1,q-(i>>1));
			printf("%d\n",solve(ct,q-ct*2,n));
		}else{
			int ct=min((i>>1)-1,q-(i>>1));
			int ans1=solve(ct,q-ct*2-1,n-1);
			int ans2=solve(ct,q-ct*2-1,n);
			printf("%d\n",(ans1+ans2)%mod);
		}
	}
	return 0;
}
