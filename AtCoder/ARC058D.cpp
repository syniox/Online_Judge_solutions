#include <cstdio>
typedef long long lint;
const int N=1e5+5;
const int mod=1e9+7;
int n,m,fac[N<<1],ifac[N<<1];

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

inline void init(){
	fac[0]=1;
	for(int i=1; i<=n+m; ++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	ifac[n+m]=fpow(fac[n+m],mod-2);
	for(int i=n+m; i>=1; --i){
		ifac[i-1]=(lint)ifac[i]*i%mod;
	}
}

inline int C(const int x,const int y){
	if(x<y) return 0;
	return (lint)fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}

int main(){
	n=nxi(),m=nxi();
	int qx=nxi(),qy=nxi();
	init();
	int ans=0;
	for(int i=qy+1; i<=m; ++i){
		ans=(ans+(lint)C((n-qx-1)+i-1,i-1)*C((qx-1)+(m-i),m-i))%mod;
	}
	printf("%d\n",ans);
	return 0;
}
