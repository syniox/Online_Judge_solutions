#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=5e5+5;
const int mod=19491001;
const int R=18827933;//I.E. fpow(7,(mod-1)/3)(原根: 7)
const int R2=(lint)R*R%mod;
int n,q,d,fac[N],ifac[N],dp[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline int fpow(int x,T t){
	int ans=1;
	for(; t; t>>=1,x=(lint)x*x%mod){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline int C(int x,int y){
	if(x<y) return 0;
	return (lint)fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}

inline void init(){
	fac[0]=1;
	for(int i=1; i<N; ++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	ifac[N-1]=fpow(fac[N-1],mod-2);
	for(int i=N-1; i; --i){
		ifac[i-1]=(lint)ifac[i]*i%mod;
	}
}

int main(){
	init();
	n=nxi(),q=nxi(),d=nxi();
	if(d==1){
		printf("%d\n",fpow(q,n));
		return 0;
	}
	else if(d==2){
		int ans=0;
		for(int i=0; i<=q; ++i){
			ans=(ans+(lint)C(q,i)*fpow((i<<1)-q,n))%mod;
		}
		ans=(lint)ans*fpow(fpow(2,mod-2),q)%mod;
		printf("%d\n",ans<0?ans+mod:ans);
	}
	else{
		int ans=0;
		for(int i=0; i<=q; ++i){
			for(int j=0; j<=q-i; ++j){
				const int tmp=fpow((i+(lint)j*R+(lint)(q-i-j)*R2)%mod,n);
				ans=(ans+(lint)tmp*C(q,i)%mod*C(q-i,j))%mod;
			}
		}
		ans=(lint)ans*fpow(fpow(3,mod-2),q)%mod;
		printf("%d\n",ans<0?ans+mod:ans);
	}
	return 0;
}
