#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=2e6+5;
const int mod=998244353;
int n,inv100,val[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline int fpow(int x,T t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

int solve(){
	static int f[N],g[N],h[N],pref[N];
	//令a[i]为得到的数组
	//f[i]: a[i]的期望, pref[i]: f[i]前缀和, g[i]: a[i]^2的期望
	//h[i]: a[i] * \sum_j a[j](1<=j<i)的期望
	int ans=0;
	for(int i=1; i<=n; ++i){
		f[i]=(lint)val[i]*(f[i-1]+1)%mod;
		pref[i]=(pref[i-1]+f[i])%mod;
		ans+=(g[i]=(g[i-1]+2ll*f[i-1]+1)*val[i]%mod);
		h[i]=(lint)val[i]*((lint)h[i-1]+g[i-1]+pref[i-1])%mod;
		ans=(ans+(lint)(h[i]<<1))%mod;
		//printf("%d %d %d ans%d\n",f[i],g[i],h[i],ans);
	}
	return (ans+mod)%mod;
}

int main(){
	inv100=fpow(100,mod-2);
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=(lint)nxi()*inv100%mod;
	}
	printf("%d\n",solve());
	return 0;
}
