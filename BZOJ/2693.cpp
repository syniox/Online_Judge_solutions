#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e7+5;
const int mod=1e8+9;
int f[N],sum[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

void sieve(){
	static int cnp,prm[N];
	static bool npr[N];
	f[1]=1;
	for(int i=2; i<N; ++i){
		if(!npr[i]){
			prm[++cnp]=i;
			f[i]=-i+1;
		}
		for(int j=1,k=i*prm[j]; j<=cnp&&k<N; ++j,k=i*prm[j]){
			npr[k]=1;
			if(i%prm[j]==0){
				f[k]=f[i];
				break;
			}
			f[k]=(f[i]*(1-prm[j]))%mod;
		}
	}
	for(int i=1; i<N; ++i){
		f[i]=(f[i-1]+(lint)i*f[i])%mod;
	}
	for(int i=1; i<N; ++i){
		sum[i]=(sum[i-1]+i)%mod;
	}
}

int main(){
	sieve();
	for(int q=nxi(); q; --q){
		int n=nxi(),m=nxi();
		if(n>m) std::swap(n,m);
		int ans=0;
		for(int i=1,j; i<=n; i=j+1){
			const int a=n/i,b=m/i;
			j=std::min(n/a,m/b);
			ans=(ans+(lint)sum[a]*sum[b]%mod*(f[j]-f[i-1]))%mod;
		}
		printf("%d\n",ans<0?ans+mod:ans);
	}
	return 0;
}
