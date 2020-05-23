#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e7+5;
const int mod=998244353;
int inv[N];

namespace utils{
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

inline void init(){
	inv[1]=1;
	for(int i=2; i<N; ++i){
		inv[i]=(lint)(mod/i+1)*inv[i-mod%i]%mod;
	}
}

int main(){
	init();
	for(int T=nxi(); T; --T){
		int n=nxi(),k=nxi(),q=nxi(),ans=0;
		if(q==1){
			puts("1");
			continue;
		}
		ans=fpow(q,n)-1;
		for(int s=1,c=1,i=1; i<=k; ++i){
			s=(lint)s*(q-1)%mod;
			c=(lint)c*(n-i+1)%mod*inv[i]%mod;
			if(i==k) ans=(lint)ans*fpow(c,mod-2)%mod;
			else ans=(ans-(lint)s*c)%mod;
		}
		ans=(lint)ans*q%mod*fpow(fpow(q-1,k),mod-2)%mod;
		printf("%d\n",(ans+mod)%mod);
	}
	return 0;
}
