#include <cstdio>
typedef long long lint;
const int N=15;
const int mod=1e9+7;
int n,m,nxt[N],dp[1<<N],cbit[1<<N];

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

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=m; ++i){
		const int a=nxi()-1,b=nxi()-1;
		nxt[a]|=1<<b;
	}
	for(int i=1; i<1<<n; ++i){
		cbit[i]=cbit[i>>1]+(i&1);
	}
	dp[3]=1;
	for(int i=4; i<1<<n; ++i){
		if((i&1)!=(i>>1&1)) continue;
		dp[i]=1;
		for(int j=(i-1)&i; j; j=(j-1)&i){
			if((j&1)!=(j>>1&1)) continue;
			const int p=i^j;
			int ws=dp[j],wt=1;
			for(int k=0; k<n&&ws; ++k){
				if(j>>k&1){
					ws=ws*((1ll<<cbit[nxt[k]&p])-1)%mod;
				}
				if(p>>k&1){
					wt=wt*(1ll<<cbit[nxt[k]&j])%mod;
				}
			}
			dp[i]=(dp[i]+(lint)ws*wt)%mod;
		}
	}
	printf("%d\n",(fpow(2,m)-dp[(1<<n)-1]+mod)%mod);
	return 0;
}
