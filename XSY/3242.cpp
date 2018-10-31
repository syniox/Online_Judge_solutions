#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=3e6+2;
const int mod=998244353;
int fac[N],inv[N];

inline char get_c(){
	static char *h,*t,buf[20000];
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=get_c())>'9'||c<'0');
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return x;
}

inline int qpow(int x,int t){
	int ans=1;
	for(;t;x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline void init(){
	fac[0]=1;
	for(int i=1;i<N;++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	inv[N-1]=qpow(fac[N-1],mod-2);
	for(int i=N-1;i;--i){
		inv[i-1]=(lint)inv[i]*i%mod;
	}
}

inline int C(const int x,const int y){
	if(x<y) return 0;
	return (lint)fac[x]*inv[y]%mod*inv[x-y]%mod;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	init();
	int T=nxi();
	while(T--){
		const int a=nxi(),b=nxi(),k=nxi();
		if((k-a-b)&1||a+b>k){
			puts("0");
			continue;
		}
		const int i=(k+a+b)>>1,j=(k-a-b)>>1;
		/*
		   C(i+j,i)*sum{l}{C(i,a+l)*C(j,l)}=
		   C(i+j,i)*sum{l}{C(i,a+l)*C(j,j-l)}
		 */
		printf("%lld\n",(lint)C(i+j,i)*C(i+j,a+j)%mod);
//		method 2:
//		printf("%lld\n",(lint)C(k,(k-a-b)>>1)*C(k,(k-a+b)>>1));
	}
	return 0;
}
