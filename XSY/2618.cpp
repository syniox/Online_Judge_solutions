#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=105;
const int mod=1e9+9;
//C[big][small]
int n,m,step,C[N][N];
lint dp[N][N];
char ca[N],cb[N];

template <class T> inline void twk(T &x){
	if(x>=mod) x-=mod;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	C[0][0]=1;
	for(int i=1;i<N;++i) C[i][0]=1;
	for(int i=1;i<N;++i){
		for(int j=1;j<=i;++j){
			twk(C[i][j]=C[i-1][j-1]+C[i-1][j]);
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("b.in","r",stdin);
#endif
	init();
	n=nxi(),step=nxi(),m=nxi();
	scanf("%s%s",ca+1,cb+1);
	int fs=0;
	for(int i=1;i<=n;++i){
		fs+=(ca[i]!=cb[i]);
	}
	dp[0][fs]=1;
	for(int i=0;i<step;++i){
		for(int j=0;j<=n;++j){
			if(!dp[i][j]) continue;
			const lint cur=dp[i][j],limit=std::min(j,m);
			for(int k=std::max(0,m-n+j);k<=limit;++k){
				const int tp=j-k+(m-k);
				if(tp>n||tp<0) continue;
				twk(dp[i+1][tp]+=(lint)cur*(lint)C[j][k]%mod*(lint)C[n-j][m-k]%mod);
			}
		}
	}
	printf("%lld\n",dp[step][0]);
	return 0;
}
