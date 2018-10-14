#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=302;
const int mod=1e9+7;
int cn[N],cm[N],pw2[N],inv[N],dp[N][N];
//dp[i][j]: i control j out

inline void twk(int &x){
	if(x>=mod) x-=mod;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
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
	for(int i=1;i<N;++i){
		inv[i]=qpow(i,mod-2);
	}
	dp[0][0]=1;
	for(int i=1;i<N;++i){
		for(int j=1;j<N;++j){
			dp[i][j]=((lint)dp[i-1][j-1]*2+(j>1?dp[i-1][j-2]:0))%mod;
		}
	}
}

inline void get_c(const int n,const int m,const int q){
	cn[0]=cm[0]=1;
	int limit=std::min(n-m,q);
	for(int i=1;i<=limit;++i){
		cn[i]=(lint)cn[i-1]*(n-m-i+1)%mod*inv[i]%mod;
	}
	limit=std::min(q,m);
	for(int i=1;i<=limit;++i){
		cm[i]=(lint)cm[i-1]*(m-i+1)%mod*inv[i]%mod;
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("d.in","r",stdin);
#endif
	init();
	int T=nxi();
	while(T--){
		const int n=nxi(),m=nxi(),q=nxi();
		get_c(n,m,q);
		int ans=0;
		for(int i=0;i<=q&&i<=m;++i){
			pw2[i]=qpow(2,m-i);
		}
		for(int i=0;i<=q;++i){
			int cnt=0;
			for(int j=(q-i)>>1;j<=m&&j<=q-i;++j){
				cnt=(cnt+(lint)pw2[j]*cm[j]%mod*dp[j][q-i])%mod;
			}
			ans=(ans+(lint)cnt*cn[i])%mod;
		}
		printf("%d\n",ans);
	}
	return 0;
}
