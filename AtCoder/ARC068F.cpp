#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=2005;
const int mod=1e9+7;
int n,q,dp[N];

inline int nxi(FILE *fd=stdin){
	int x=0;
	char c;
	while((c=fgetc(fd))>'9'||c<'0');
	while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
	return x;
}

template <class T> inline int fpow(int x,T t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

int main(){
	n=nxi(),q=nxi();
	dp[n+1]=1;
	for(int i=1; i<q; ++i){
		int sum=0;
		for(int j=n-i+2; j>1; --j){
			sum=(sum+dp[j])%mod;
			dp[j]=sum;
		}
	}
	int ans=0;
	for(int i=2; i<=n-q+2; ++i){
		ans=(ans+dp[i])%mod;
	}
	if(q==1) ans=1;
	printf("%lld\n",(lint)ans*(q==n?1:fpow(2,n-q-1))%mod);
	return 0;
}
