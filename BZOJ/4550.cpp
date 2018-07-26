#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
typedef long long lint;
const int N=10002;
const int mod=1e9+7;
int n,k,d,jc[N],cj[N],dp[N];

inline int C(int n,int k){
	return (lint)jc[n]*cj[k]%mod*cj[n-k]%mod;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

inline lint qpow(lint x,int t){
	lint ans=1;
	for(;t;t>>=1,x=x*x%mod){
		if(t&1) ans=ans*x%mod;
	}
	return ans;
}

inline void init(){
	jc[0]=1;
	for(int i=1;i<N;++i){
		jc[i]=(lint)jc[i-1]*i%mod;
	}
	cj[N-1]=qpow(jc[N-1],mod-2);
	for(int i=N-1;i;--i){
		cj[i-1]=(lint)cj[i]*i%mod;
	}
}

inline int highbit(unsigned n){
	int ans=0;
	if(n>>16) ans+=16,n>>=16;
	if(n>>8) ans+=8,n>>=8;
	if(n>>4) ans+=4,n>>=4;
	if(n>>2) ans+=2,n>>=2;
	if(n>>1) ans+=1,n>>=1;
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	init();
	n=nxi(),k=nxi(),d=nxi();
	int bit=highbit((n-k)/(d+1));
	dp[n-k]=1;
	for(int i=0;i<=bit;++i){
		for(int j=(n-k)%(d+1);j<=n-k;j+=d+1){
			for(int l=1;l*(d+1)*(1<<i)<=n-k-j&&l*(d+1)<=k>>1;++l){
				dp[j]=(dp[j]+(lint)dp[l*(d+1)*(1<<i)+j]*C(k>>1,l*(d+1)))%mod;
			}
		}
	}
	lint ans=0;
	for(int i=0;i<=n-k;++i){
		ans=(ans+(lint)dp[i]*C(i+(k>>1),k>>1))%mod;
	}
	printf("%lld\n",(C(n,k)-ans+mod)%mod);
	return 0;
}
