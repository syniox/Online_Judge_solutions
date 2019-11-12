#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e6+5;
const int mod=1e9+7;
int n,pw10[N],fac[N*5],ifac[N*5];

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

inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

void init(){
	pw10[0]=1;
	for(int i=1; i<N; ++i){
		pw10[i]=pw10[i-1]*10ll%mod;
	}
	fac[0]=1;
	for(int i=1; i<N*5; ++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	ifac[N*5-1]=fpow(fac[N*5-1],mod-2);
	for(int i=N*5-1; i; --i){
		ifac[i-1]=(lint)ifac[i]*i%mod;
	}
}

inline int C(const int x,const int y){
	if(x<y) return 0;
	return (lint)fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}

inline int get_num(const int x){
	//return x%10?0:(x/10&1?mod-C(n,x/10):C(n,x/10));
	return x&1?mod-C(n,x):C(n,x);
}

inline int get_denom(const int x){
	return C(x+n-1,x);
}

inline int get_ans(const int x){
	int ans=0;
	for(int i=0; i<=x; i+=10){
		ans=(ans+(lint)get_num(i/10)*get_denom(x-i))%mod;
	}
	return ans;
}

int main(){
	init();
	for(int T=nxi(); T; --T){
		n=nxi();
		if((n&1)==0){
			printf("%d\n",pw10[n>>1]);
			continue;
		}
		if((n&3)==1){
			n=(n-1)>>1;
			if(!n){
				puts("1");
				continue;
			}
			int ans=0;
			for(int i=0; i<=4; ++i){
				ans=(ans+get_ans(n/2*9+i))%mod;
			}
			printf("%d\n",ans);
		}
		else{
			assert((n&3)==3);
			n=(n-3)>>1;
			if(!n){
				puts("5");
				continue;
			}
			int ans=0;
			for(int i=0; i<=9; ++i){
				int res=get_ans(n/2*9+i);
				ans=(ans+std::min(10ll-i,5ll)*res)%mod;
				if(i&&i<5) ans=(ans+(5ll-i)*res)%mod;
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
